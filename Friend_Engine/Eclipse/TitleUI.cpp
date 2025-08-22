#include "TitleUI.h"
#include "../Direct2D_EngineLib/GameApp.h"
#include "EclipseApp.h"

void TitleUI::Awake()
{
	// audio source ������Ʈ ����
	bgmSource = AddComponent<AudioSource>();
	sfxSource = AddComponent<AudioSource>();

	// audio clip ���ҽ� ����
	bgmClip = ResourceManager::Get().CreateAudioClip("../Resource/Audio/UI/BGM/s_Title.wav");
	sfxClip_Button1 = ResourceManager::Get().CreateAudioClip("../Resource/Audio/UI/SFX/Button/s_Button_1.wav");
	sfxClip_Button2 = ResourceManager::Get().CreateAudioClip("../Resource/Audio/UI/SFX/Button/s_Button_2.wav");

	// audioSource ä�� �׷� ���� �� ���� ���
	bgmSource->SetChannelGroup(AudioSystem::Get().GetBGMGroup());
	bgmSource->SetVolume(1);
	std::wostringstream oss;
	oss << L"float = " << std::fixed << std::setprecision(2) << bgmSource->GetVolume() << L"\n"; // 2�ڸ�
	OutputDebugStringW(oss.str().c_str());

	bgmSource->SetClip(bgmClip);
	bgmSource->SetLoop(true);
	bgmSource->Play();

	sfxSource->SetChannelGroup(AudioSystem::Get().GetSFXGroup());
	sfxSource->SetClip(sfxClip_Button1);
	sfxSource->SetLoop(false);

	linecontroller = new LineController();
}

void TitleUI::SceneStart()
{
	menuButtons = { play_Button, options_Button, credit_Button, end_Button };
	optionButtons = { optionUI->sound_Button,optionUI->key_Button };
	backgroundImage->AddComponent<Transform>();
	backgroundImage->AddComponent<SpriteRenderer>();
	titleLogo_Image->AddComponent<Transform>();
	titleLogo_Image->AddComponent<SpriteRenderer>();
	titleSpell_Image->AddComponent<Transform>();
	titleSpell_Image->AddComponent<SpriteRenderer>();
	auto title = ResourceManager::Get().CreateTexture2D("../Resource/mo/TitleBackGround.png");
	backgroundImage->GetComponent<SpriteRenderer>()->sprite = ResourceManager::Get().CreateSprite(title, "TitleBackGround");

	auto logo = ResourceManager::Get().CreateTexture2D("../Resource/mo/Title_Logo.png");
	titleLogo_Image->GetComponent<SpriteRenderer>()->sprite = ResourceManager::Get().CreateSprite(logo, "Title_Logo");
	titleLogo_Image->GetComponent<SpriteRenderer>()->renderMode = RenderMode::Lit_Glow;;

	auto spell = ResourceManager::Get().CreateTexture2D("../Resource/mo/Title_Spell.png");
	titleSpell_Image->GetComponent<SpriteRenderer>()->sprite = ResourceManager::Get().CreateSprite(spell, "Title_Spell");
	//titleSpell_Image->GetComponent<SpriteRenderer>()->renderMode = RenderMode::Lit_Glow;

	options_Button->rectTransform->SetParent(play_Button->rectTransform);
	credit_Button->rectTransform->SetParent(play_Button->rectTransform);
	end_Button->rectTransform->SetParent(play_Button->rectTransform);

	play_Button->rectTransform->SetPosition(0, -250);
	play_Button->rectTransform->SetSize(300, 50);
	play_Button->imageRenderer->SetBaseColor(D2D1::ColorF(D2D1::ColorF::LightPink, 0));

	options_Button->rectTransform->SetPosition(0, -50);
	options_Button->rectTransform->SetSize(300, 50);
	options_Button->imageRenderer->SetBaseColor(D2D1::ColorF(D2D1::ColorF::LightPink,0));

	credit_Button->rectTransform->SetPosition(0, -100);
	credit_Button->rectTransform->SetSize(300, 50);
	credit_Button->imageRenderer->SetBaseColor(D2D1::ColorF(D2D1::ColorF::LightPink, 0));

	end_Button->rectTransform->SetPosition(0, -150);
	end_Button->rectTransform->SetSize(300, 50);
	end_Button->imageRenderer->SetBaseColor(D2D1::ColorF(D2D1::ColorF::LightPink,0));

	play_Button->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::White));
	play_Button->screenTextRenderer->SetText(L"�����ϱ�");
	play_Button->screenTextRenderer->SetFontSize(30);
	play_Button->screenTextRenderer->SetFontName(L"���°���ü");
	options_Button->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::White));
	options_Button->screenTextRenderer->SetText(L"�ɼ�");
	options_Button->screenTextRenderer->SetFontSize(30);
	options_Button->screenTextRenderer->SetFontName(L"���°���ü");
	credit_Button->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::White));
	credit_Button->screenTextRenderer->SetText(L"ũ����");
	credit_Button->screenTextRenderer->SetFontSize(30);
	credit_Button->screenTextRenderer->SetFontName(L"���°���ü");
	end_Button->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::White));
	end_Button->screenTextRenderer->SetText(L"������");
	end_Button->screenTextRenderer->SetFontSize(30);
	end_Button->screenTextRenderer->SetFontName(L"���°���ü");

	// ���� �̹���
	underscore_Image->AddComponent<Animator>();
	underscore_Image->GetComponent<Animator>()->SetController(linecontroller);
	underscore_Image->rectTransform->SetPosition(0, -20);
	underscore_Image->rectTransform->SetSize(150, 150);
	underscore_Image->imageRenderer->layer = 10;
	underscore_Image->SetActive(false); // �ʱ⿡�� ���� �̹��� ��Ȱ��ȭ

	// �ɼ� UI ����
	optionUI->SetActive(false);
	optionUI->rectTransform->SetPosition(0, 0);


	play_Button->button->onClickListeners.AddListener(
		this, std::bind(&TitleUI::ChangePlayScene, this));

	options_Button->button->onClickListeners.AddListener(
		this, std::bind(&TitleUI::OpenOptionUI, this));

	credit_Button->button->onClickListeners.AddListener(
		this, std::bind(&TitleUI::OpenCreditUI, this));

	for (UI_Button* btn : menuButtons)
	{
		btn->button->onPointEnterListeners.AddListener(
			this, std::bind(&TitleUI::OnPointEnterButton, this, btn));

		btn->button->onPointExitListeners.AddListener(
			this, std::bind(&TitleUI::OnPointExitButton, this, btn));
	}

	for (UI_Button* btn : optionButtons)
	{
		btn->button->onClickListeners.AddListener(
			this, std::bind(&TitleUI::OnClickOptionUI, this,btn));
	}


	optionUI->close_Button->button->onClickListeners.AddListener(
		this, [this]() {
			sfxSource->SetClip(sfxClip_Button2);
			sfxSource->Play(); 
			play_Button->SetActive(true);
			optionUI->SetActive(false);
			underscore_Image->rectTransform->SetPosition(0, -20);
			underscore_Image->rectTransform->SetSize(150, 150);
		});


	creditUI->close_Button->button->onClickListeners.AddListener(
		this, [this]() {
			sfxSource->SetClip(sfxClip_Button2);
			sfxSource->Play();
			play_Button->SetActive(true);
			creditUI->creditWindowBackGround_Image->SetActive(false);
			underscore_Image->rectTransform->SetPosition(0, -20);
			underscore_Image->rectTransform->SetSize(150, 150);
		});

	end_Button->button->onClickListeners.AddListener(
		this, [this]() {
			sfxSource->SetClip(sfxClip_Button2);
			sfxSource->Play(); 
			GameApp::Quit(); });
}

void TitleUI::Update()
{
	titleSpell_Image->transform->Rotate(5 * Time::GetDeltaTime());

	glowtimer += Time::GetDeltaTime();  // �� ������ �ð� ����

	float s = sinf(glowtimer * glowspeed) * 0.5f + 0.5f;
	s = pow(s, 6.0f);
	float glow = s * 150.0f;
	titleLogo_Image->GetComponent<SpriteRenderer>()->SetGlowAmmount(glow);


	if (Input::GetKeyDown(VK_ESCAPE)&&(optionUI->IsActive()|| creditUI->creditWindowBackGround_Image->IsActive()))
	{
		play_Button->SetActive(true);
		optionUI->SetActive(false);
		creditUI->creditWindowBackGround_Image->SetActive(false);
		underscore_Image->rectTransform->SetPosition(0, -20);
		underscore_Image->rectTransform->SetSize(150, 150);
	}
}

void TitleUI::Destroyed()
{
	delete linecontroller;
}

void TitleUI::OnPointEnterButton(UI_Button* onButton)
{
	prevHoverButton = onButton;
	onButton->imageRenderer->SetAlpha(1);
	underscore_Image->rectTransform->SetParent(onButton->rectTransform);
	underscore_Image->SetActive(true);

	sfxSource->SetClip(sfxClip_Button1);
	sfxSource->Play();
	linecontroller->PlayAnimation("UI_Line");
}

void TitleUI::OnPointExitButton(UI_Button* currButton)
{
	if (prevHoverButton == currButton)
		underscore_Image->SetActive(false);
}

void TitleUI::OnClickOptionUI(UI_Button* button)
{
	RectTransform* target = nullptr;

	if (button == optionUI->sound_Button)
	{
		target = optionUI->sound_Button->rectTransform;
		optionUI->soundBase_Image->SetActive(true);
		optionUI->controlKeyBase_Image->SetActive(false);
	}
	else if (button == optionUI->key_Button)
	{
		target = optionUI->key_Button->rectTransform;
		optionUI->soundBase_Image->SetActive(false);
		optionUI->controlKeyBase_Image->SetActive(true);
	}

	if (target && underscore_Image->rectTransform->GetParent() != target)
		underscore_Image->rectTransform->SetParent(target);

	linecontroller->PlayAnimation("UI_Line");
	sfxSource->SetClip(sfxClip_Button2);
	sfxSource->Play();
}

void TitleUI::OpenOptionUI()
{
	underscore_Image->rectTransform->SetParent(optionUI->sound_Button->rectTransform);
	underscore_Image->SetActive(true);
	underscore_Image->rectTransform->SetPosition(0, -30);
	underscore_Image->rectTransform->SetSize(200, 150);

	optionUI->SetActive(true);
	optionUI->controlKeyBase_Image->SetActive(false);
	play_Button->SetActive(false);
	sfxSource->SetClip(sfxClip_Button2);
	sfxSource->Play();
}

void TitleUI::OpenCreditUI()
{
	underscore_Image->rectTransform->SetParent(creditUI->creditTitle_Text->rectTransform);
	underscore_Image->SetActive(true);
	underscore_Image->rectTransform->SetPosition(0, -30);
	underscore_Image->rectTransform->SetSize(200, 150);

	creditUI->creditWindowBackGround_Image->SetActive(true);
	play_Button->SetActive(false);
	sfxSource->SetClip(sfxClip_Button2);
	sfxSource->Play();
}


void TitleUI::ChangePlayScene()
{
	sfxSource->SetClip(sfxClip_Button2);
	sfxSource->Play();
	SceneManager::Get().ChangeScene(EclipseApp::PLAY);
}
