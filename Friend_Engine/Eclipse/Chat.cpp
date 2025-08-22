#include "Chat.h"
#include "Typer.h"
#include "../Friend_2D_EngineLib/Input.h"
#include "../Friend_2D_EngineLib/AudioSource.h"

Chat::Chat()
{
	chatText = GameManager::Get().g_playUI->chat_Text;
	curchatCondition = ChatCondition::Quest;
	// ����Ʈ 0
	AddChat(0, ChatCondition::Quest, L"����... �˰� ���������.");
	AddChat(0, ChatCondition::Quest, L"��� �ӿ���... Ÿ���� ��ȥ���� ����� �ִ�...");
	AddChat(0, ChatCondition::Quest, L"����� ������ �ʱ⸦...");
	AddChat(0, ChatCondition::Quest, L"... ���� �����.");
	AddChat(0, ChatCondition::Quest, L"������ � ������ �Ƴ�?");
	AddChat(0, ChatCondition::Quest, L"�ϴ��� �������� ������ ��... �׸��� 'ȥ��'�� ������ �����̴�.");
	AddChat(0, ChatCondition::Quest, L"Ÿ���� ��ȥ���� �ϴÿ��� ������� �ִ�.");
	AddChat(0, ChatCondition::Quest, L"�̹���... ���Ƴ� ���簡 ����.");
	AddChat(0, ChatCondition::Quest, L"������ �� �ȿ�, �� ������ ȥ�� ���� �ִ�.");
	AddChat(0, ChatCondition::Quest, L"�� ���� ������� ���� ������ �� �˾ƾ���.");
	AddChat(0, ChatCondition::Quest, L"�ϴ� ������ Ǯ���. SPACE BAR�� �����ϰ�,\nA�� D�� ���� �¿�� ������ �� �־�.");

	// ����Ʈ 1
	AddChat(1, ChatCondition::Quest, L"��Ŭ������ ������ �����ϰ�,\n���� �߿� �����ϸ�... �ð��� ��������.");
	AddChat(1, ChatCondition::Quest, L"�׸��� ������ ���ϰ� ���� ���� SHIFT�� ���� ������.");
	AddChat(1, ChatCondition::Quest, L"�� ���� �� Ȱ���ϵ���.");

	// ���̺� ���� 0
	AddChat(0, ChatCondition::Wave, L"QŰ�� ���� ����� ����� �� �ְ�,\nEŰ�� �����Ͽ� ������ �ϰ��� ���� ���� ����.");
	AddChat(0, ChatCondition::Wave, L"���� �����δ� �� �տ� �޷ȴ�.");
	AddChat(0, ChatCondition::Wave, L"�׵��� �ٰ����� �ִ�. ���� ���ϸ�, ���� �ǵ��� �� ����.\n(��ȥ�� 10ȸ óġ�ϼ���.)");

	// ���̺� ���� 1
	AddChat(1, ChatCondition::Success, L"��ó��� ���� ���� �� �ְھ�. ������ ����� �ݹ��̾�.");
	AddChat(1, ChatCondition::Success, L"�� ���� ���� ���� �������� �ʾ�.\n�ο򿡼� ���� ȥ���� �� �ɷ��� Ű����.");
	AddChat(1, ChatCondition::Success, L"TAB�� ���� ��. ���ο� ���� ��� �� ���� �ž�.");

	AddChat(1, ChatCondition::Fail, L"ȥ���� ������ ������ �־�. �� �ż��� ���Ŀ� �ž�.");
	AddChat(1, ChatCondition::Fail, L"�� ���� ���� ���� �������� �ʾ�.\n�ο򿡼� ���� ȥ���� �� �ɷ��� Ű����.");
	AddChat(1, ChatCondition::Fail, L"TAB�� ���� ��. ���ο� ���� ��� �� ���� �ž�.");


	//  ���̺� ���� 1
	AddChat(1, ChatCondition::Wave, L"���� ������ �ڸ� ��ұ�...\nȥ���� ������ ������ �ʴ� ��, ����� ������ ������ ���̴�.");
	AddChat(1, ChatCondition::Wave, L"������ ����ƶ�... ���� �� ƴ�� ������.\n(���⸦ 5ȸ �����ϼ���.)");

	// ���̺� ���� 2 
	AddChat(2, ChatCondition::Success, L"����, ���ݱ����� �� �����. ������ �� ��ǳ�� �������.");
	AddChat(2, ChatCondition::Success, L"ȥ�� ��Ƶ� �� ���� �ʾҰ���?\n���ο� �ɷ��� ������.");

	AddChat(2, ChatCondition::Fail, L"�� �ӵ��δ� ��Ƽ�� �����. ���� ������ �ݵ�� ���Ƴ��� �Ѵ�.");
	AddChat(2, ChatCondition::Fail, L"ȥ�� ��Ƶ� �� ���� �ʾҰ���?\n���ο� �ɷ��� ������.");

	// ���̺� ���� 2
	AddChat(2, ChatCondition::Wave, L"�̹��� Ÿ������ ���� ȥ�� �������� �־�.\n�� ��ȥ�� ���ѳ���.\n(�糪�� ��ȣ�ϼ���.)");

	// ���̺� ���� 3
	AddChat(3, ChatCondition::Success, L"�� ���п� �� ���� ������ �ʾҴ�.");
	AddChat(3, ChatCondition::Success, L"�̹� ������ ���� ȥ�� ���� ����.");
	AddChat(3, ChatCondition::Success, L"�� �������� �������� ���ѳ� �� �ִ�.\n(�콺�� óġ�ϼ���.)");

	AddChat(3, ChatCondition::Fail, L"�� ���� ���� ��ŭ, �� ���� ���� ����� ���̴�.");
	AddChat(3, ChatCondition::Quest, L"�̹� ������ ���� ȥ�� ���� ����.");
	AddChat(3, ChatCondition::Quest, L"�� �������� �������� ���ѳ� �� �ִ�.\n(�콺�� óġ�ϼ���.)");

	// ���̺� ���� 3
	AddChat(3, ChatCondition::Wave, L"����, ƴ�� ����, �ڷ� ������ ���� ����. �׸� ���ƾ� ��.\n(�콺�� óġ�ϼ���.)");

	// ���̺� 4
	AddChat(4, ChatCondition::Success, L"...������. �޺��� ���ƿ���, ȥ���� ������.");
	AddChat(4, ChatCondition::Success, L"�ʴ� �� ���� ���� ��, �׸��� ������ ȥ�� ���� �ڷ� ���� ���̴�.");
	AddChat(4, ChatCondition::Success, L"������ �� �ٸ� ���� ã�ƿ´ٸ�... ���� �̸��� �ٽ� �Ҹ� ���̴�.");
	AddChat(4, ChatCondition::Success, L"���� ����. �װ� ���ѳ� ���� ������.");

	sequence.push_back({ ChatCondition::Quest, 0 });
	sequence.push_back({ ChatCondition::Quest, 1 });
	sequence.push_back({ ChatCondition::Wave, 0 });
	sequence.push_back({ ChatCondition::Success, 1 });
	sequence.push_back({ ChatCondition::Wave, 1 });
	sequence.push_back({ ChatCondition::Success, 2 });
	sequence.push_back({ ChatCondition::Wave, 2 });
	sequence.push_back({ ChatCondition::Success, 3 });
	sequence.push_back({ ChatCondition::Wave, 3 });
	sequence.push_back({ ChatCondition::Success, 4 });

	SetCondition();
	chatText->screenTextRenderer->SetText(currentLines[chatCount]);
}

void Chat::Awake()
{
}
void Chat::Update()
{

}

//�÷��̾� ���ͷ��� �� ȣ�� �Լ�
void Chat::NextChat()
{
	if (!finished)
	{
		if (!chatText->GetComponent<Typer>()->IsTypingEnd())
		{
			chatText->GetComponent<Typer>()->EndTyping();
		}
		else
		{
			chatCount++;
			/*chatText->screenTextRenderer->SetText(currentLines[chatCount]);*/

			chatText->GetComponent<Typer>()->SetTextRenderer(chatText->screenTextRenderer);
			chatText->GetComponent<Typer>()->SetAudioSource(chatText->GetComponent<AudioSource>());
			chatText->GetComponent<Typer>()->StartTyping(currentLines[chatCount]);
			if (chatCount == currentLines.size() - 1)
			{
				finished = true;
				GameManager::Get().g_playUI->chat_Button->SetActive(true);
				GameManager::Get().g_playUI->chatNext_Image->SetActive(false);
			}
		}
	}
	else
	{
		if (!chatText->GetComponent<Typer>()->IsTypingEnd())
		{
			chatText->GetComponent<Typer>()->EndTyping();
		}
	}
}

void Chat::AddChat(int index, ChatCondition condition, const std::wstring& line)
{
	// ���� �׷��� �ִ��� �˻�
	for (auto& group : chatGroups)
	{
		if (group.Index == index && group.condition == condition)
		{
			group.lines.push_back(line);
			return;
		}
	}

	// ������ �� �׷� ����
	WaveChatGroup newGroup;
	newGroup.Index = index;
	newGroup.condition = condition;
	newGroup.lines.push_back(line);

	chatGroups.push_back(newGroup);
}

void Chat::SetCondition(ChatCondition chatCondition)
{
	ChatStep seq = sequence[sequenceCount++];
	chatCount = 0;
	finished = false;
	currentLines.clear();
	if (chatCondition == ChatCondition::Quest) chatCondition = seq.condition;
	curchatCondition = seq.condition;
	GameManager::Get().questState = curchatCondition;

	// index�� ����Ʈ ��ȣ �Ǵ� ���̺� ��ȣ
	for (const auto& group : chatGroups)
	{
		if (group.Index == seq.index && group.condition == chatCondition)
		{
			currentLines.insert(currentLines.end(), group.lines.begin(), group.lines.end());
		}
	}

	/*chatText->screenTextRenderer->SetText(currentLines[chatCount]);*/
	chatText->GetComponent<Typer>()->SetTextRenderer(chatText->screenTextRenderer);
	chatText->GetComponent<Typer>()->SetAudioSource(chatText->GetComponent<AudioSource>());
	chatText->GetComponent<Typer>()->StartTyping(currentLines[chatCount]);


	if (currentLines.size() == 1) finished = true;
}