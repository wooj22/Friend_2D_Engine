#include "Typer.h"
#include "../Friend_2D_EngineLib/ScreenTextRenderer.h"
#include "../Friend_2D_EngineLib/AudioSource.h"
#include "../Friend_2D_EngineLib/AudioClip.h"
#include "../Friend_2D_EngineLib/ResourceManager.h"
#include "../Friend_2D_EngineLib/Time.h"
#include "../Friend_2D_EngineLib/Input.h"
#include <cstdlib>
#include <ctime>

void Typer::Awake()
{
    // Sound Clip
    typingSound[0] = ResourceManager::Get().CreateAudioClip("../Resource/Woo/Sound/Typing/Typing1.wav");
    typingSound[1] = ResourceManager::Get().CreateAudioClip("../Resource/Woo/Sound/Typing/Typing2.wav");
    typingSound[2] = ResourceManager::Get().CreateAudioClip("../Resource/Woo/Sound/Typing/Typing3.wav");

    // seed
    srand((unsigned int)time(nullptr));
}

void Typer::Update()
{
	TypingDirecting();
}

// Ÿ���� ����
// cur_text�� target_text�� �� ������ typingSpeed��� ���ھ� ġ�� ����
// ���Ⱑ ������ spacingDelay��ŭ �����ٰ� ���� �̾�ģ��.
// Ÿ������ ��� �Ϸ��ϸ� isTyping�� true�� �ȴ�.
void Typer::TypingDirecting()
{
	if (!isTyping || target_text.empty() || !textRenderer || !audioSource)
		return;

	timer += Time::GetDeltaTime();

    if (cur_text.size() < target_text.size())
    {
        wchar_t nextChar = target_text[cur_text.size()];

        // ���� ������
        float delay = (nextChar == L' ') ? spacingDelay : 1.0f / typingSpeed;

        if (timer >= delay)
        {
            cur_text += nextChar;
            textRenderer->SetText(cur_text);
            timer = 0.0f;

            // sound
		    soundIndex = rand() % SOUND_COUNT;
			audioSource->SetClip(typingSound[soundIndex]);
			audioSource->PlayOneShot();
        }
    }
    else
    {
        // Ÿ���� �Ϸ�
        isTyping = false;
        timer = 0.0f;
    }
}

// Ÿ���� ����
void Typer::StartTyping(wstring text)
{
	target_text = text;
	cur_text = L"";
	isTyping = true;
}

// Ÿ���� ����
void Typer::EndTyping()
{
	cur_text = target_text;
	textRenderer->SetText(cur_text);
	isTyping = false;
}
