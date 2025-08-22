#define NOMINMAX
#include "PlayUI.h"
#include "Chat.h"
#include "Quest.h"
#include "NPC.h"
#include "EclipseApp.h"
#include "FadeManager.h"
#include "BossController.h"
#include "../Friend_2D_EngineLib/Input.h"
#include "../Friend_2D_EngineLib/InvokeSystem.h"
#include <algorithm>

void PlayUI::Awake()
{  
	soundManager = AddComponent<SoundManager>();
	soundManager->FadeInMaster(2);
	success_Text = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Text>();
	fail_Text = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Text>();
	//fail_Button = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Button>();

	//�ش� ���� ���� ������Ʈ ����
	timer_Image = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Image>();
	timer_Text = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Text>();
	stop_Button = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Button>();
	pauseWindow = SceneManager::Get().GetCurrentScene()->CreateObject<PauseWindow>();
	quest_Image = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Image>();
	questName_Text = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Text>();
	quest_Text = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Text>();
	quest2_Text = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Text>();
	quest3_Text = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Text>();
	questCount_Text = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Text>();
	chat_Image = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Image>();
	chatNext_Image = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Image>();
	chat_Text = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Text>();
	chat_Button = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Button>();
	hon_Image = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Image>();
	hon_Text = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Text>();
	skill1Icon_Image = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Image>();
	skill1_Image = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Image>();
	skill1CollTimeFilter_Image = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Image>();
	skill1Key_Image = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Image>();
	skill2Icon_Image = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Image>();
	skill2_Image = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Image>();
	skill2Key_Image = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Image>();
	waveInfo_Image = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Image>();
	skillWindowBackGround_Image = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Image>();
	skillWindowBackGroundGradient_Image = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Image>();
	skillWindow_Image = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Image>();
	skillWindowSplitter_Image = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Image>();
	skillWindowName_Image = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Image>();
	skillButtons.push_back(SceneManager::Get().GetCurrentScene()->CreateObject<SkillWindowButton>({ 0,0 }, nullptr, SkillType::MoveSpeedUp));
	skillButtons.push_back(SceneManager::Get().GetCurrentScene()->CreateObject<SkillWindowButton>({ 0,0 }, nullptr, SkillType::AttackRangeUp));
	skillButtons.push_back(SceneManager::Get().GetCurrentScene()->CreateObject<SkillWindowButton>({ 0,0 }, nullptr, SkillType::KnockbackDistanceUp));
	skillButtons.push_back(SceneManager::Get().GetCurrentScene()->CreateObject<SkillWindowButton>({ 0,0 }, nullptr, SkillType::DoubleJump));
	skillButtons.push_back(SceneManager::Get().GetCurrentScene()->CreateObject<SkillWindowButton>({ 0,0 }, nullptr, SkillType::WallJump));
	skillButtons.push_back(SceneManager::Get().GetCurrentScene()->CreateObject<SkillWindowButton>({ 0,0 }, nullptr, SkillType::JumpAttackExtra));
	skillButtons.push_back(SceneManager::Get().GetCurrentScene()->CreateObject<SkillWindowButton>({ 0,0 }, nullptr, SkillType::Dash));
	skillButtons.push_back(SceneManager::Get().GetCurrentScene()->CreateObject<SkillWindowButton>({ 0,0 }, nullptr, SkillType::SkillCooldownDown));
	skillButtons.push_back(SceneManager::Get().GetCurrentScene()->CreateObject<SkillWindowButton>({ 0,0 }, nullptr, SkillType::FastFall));
	skillHonBig_Image = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Image>();
	skillHon_Image = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Image>();
	skillHon_Text = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Text>();
	skillWindowClose_Button = SceneManager::Get().GetCurrentScene()->CreateObject<UI_Button>();
	bossHP = SceneManager::Get().GetCurrentScene()->CreateObject<BossHP>();
	npc = SceneManager::Get().GetCurrentScene()->CreateObject<NPC>({ 0,-800 });
	tooltip1 = SceneManager::Get().GetCurrentScene()->CreateObject<tooltip>();
	tooltip2 = SceneManager::Get().GetCurrentScene()->CreateObject<tooltip>();

	chatTyper = chat_Text->AddComponent<Typer>();
	success_Text->AddComponent<Typer>();
	fail_Text->AddComponent<Typer>();

	chatAudioSource = chat_Text->AddComponent<AudioSource>();
	chatAudioSource->SetChannelGroup(AudioSystem::Get().GetSFXGroup());
	chatAudioSource->SetLoop(false);

	successAudioSource = success_Text->AddComponent<AudioSource>();
	successAudioSource->SetChannelGroup(AudioSystem::Get().GetSFXGroup());
	successAudioSource->SetLoop(false);

	failAudioSource = fail_Text->AddComponent<AudioSource>();
	failAudioSource->SetChannelGroup(AudioSystem::Get().GetSFXGroup());
	failAudioSource->SetLoop(false);

	// audio source ������Ʈ ����
	bgmSource = AddComponent<AudioSource>();
	sfxSource = AddComponent<AudioSource>();

	// audio clip ���ҽ� ����
	bgmClip_Main = ResourceManager::Get().CreateAudioClip("../Resource/Audio/UI/BGM/s_Main.wav");
	bgmClip_Wave = ResourceManager::Get().CreateAudioClip("../Resource/Audio/UI/BGM/s_Battle.wav");
	bgmClip_Boss = ResourceManager::Get().CreateAudioClip("../Resource/Audio/UI/BGM/s_Boss.wav");
	bgmClip_Clear = ResourceManager::Get().CreateAudioClip("../Resource/Audio/UI/BGM/s_Clear.wav");
	
	sfxClip_Button1 = ResourceManager::Get().CreateAudioClip("../Resource/Audio/UI/SFX/Button/s_Button_1.wav");
	sfxClip_Button2 = ResourceManager::Get().CreateAudioClip("../Resource/Audio/UI/SFX/Button/s_Button_2.wav");
	sfxClip_SkillUI = ResourceManager::Get().CreateAudioClip("../Resource/Audio/UI/SFX/SkillUI/s_SkillUI.wav");
	sfxClip_SkillActive = ResourceManager::Get().CreateAudioClip("../Resource/Audio/UI/SFX/SKillUI/s_Skillactive.wav");
	sfxClip_GameOver = ResourceManager::Get().CreateAudioClip("../Resource/Audio/UI/SFX/Scene/s_Defeat.wav");
	//sfxClip_ChangeScene = ResourceManager::Get().CreateAudioClip("../Resource/Audio/UI/SFX/Scene/s_Fadeinout.wav");
	

	// audioSource ä�� �׷� ���� �� ���� ���
	bgmSource->SetChannelGroup(AudioSystem::Get().GetBGMGroup());
	sfxSource->SetChannelGroup(AudioSystem::Get().GetSFXGroup());
	//bgmSource->SetVolume(1);
	bgmSource->SetLoop(true);
	bgmSource->SetClip(bgmClip_Main);
	bgmSource->Play();

	sfxSource->SetLoop(false);
	sfxSource->SetClip(sfxClip_Button1);
}

void PlayUI::SceneStart()
{
	fade = GameObject::Find("FadeManager")->GetComponent<FadeManager>();

	success_Text->screenTextRenderer->SetFontName(L"���°���ü");
	fail_Text->screenTextRenderer->SetFontName(L"���°���ü");
	//fail_Button->screenTextRenderer->SetText(L"�ٽ��ϱ�");
	//fail_Button->screenTextRenderer->SetFontName(L"���°���ü");
	success_Text->screenTextRenderer->SetFontSize(100);
	success_Text->rectTransform->SetSize(1920,200);
	fail_Text->screenTextRenderer->SetFontSize(100);
	fail_Text->rectTransform->SetSize(1920, 200);
	//fail_Button->screenTextRenderer->SetFontSize(50);
	//fail_Button->rectTransform->SetPosition(0, -400);
	//fail_Button->rectTransform->SetSize(1920, 200);
	//fail_Button->imageRenderer->SetColor(0,0,0);
	success_Text->screenTextRenderer->layer = 31;
	fail_Text->screenTextRenderer->layer = 31;
	//fail_Button->screenTextRenderer->layer = 31;
	success_Text->SetActive(false);
	fail_Text->SetActive(false);
	//fail_Button->SetActive(false);

	success_Text->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::White));
	success_Text->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::White));
	//fail_Button->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::White));


	pauseCheckButtos = { stop_Button, pauseWindow->close_Button, pauseWindow->continuGame_Button };

	// ���̺� Ÿ�̸� UI
	timer_Image->rectTransform->SetPosition(0, 360);
	timer_Image->rectTransform->SetSize(190, 190);
	auto timerTexture = ResourceManager::Get().CreateTexture2D("../Resource/mo/Timer.png");
	timer_Image->imageRenderer->sprite = ResourceManager::Get().CreateSprite(timerTexture, "Timer");

	timer_Text->rectTransform->SetPosition(0, 380);
	timer_Text->rectTransform->SetSize(500, 40);
	timer_Text->screenTextRenderer->SetFontSize(70);
	timer_Text->screenTextRenderer->SetFontName(L"���°���ü");
	timer_Text->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::White));
	timer_Text->screenTextRenderer->layer = 1;

	timer_Text->SetActive(false);
	timer_Image->SetActive(false);

	waveInfo_Image->rectTransform->SetSize(631, 346);
	waveInfo_Image->SetActive(false);

	// �Ͻ� ���� ��ư
	stop_Button->rectTransform->SetPosition(920, 500);
	stop_Button->rectTransform->SetSize(60, 60);
	auto stopButtonTexture = ResourceManager::Get().CreateTexture2D("../Resource/mo/StopButton.png");
	stop_Button->imageRenderer->sprite = ResourceManager::Get().CreateSprite(stopButtonTexture, "StopButton");

	
	// ����Ʈ â UI
	questName_Text->rectTransform->SetParent(quest_Image->rectTransform);
	quest_Text->rectTransform->SetParent(quest_Image->rectTransform);
	quest2_Text->rectTransform->SetParent(quest_Image->rectTransform);
	quest3_Text->rectTransform->SetParent(quest_Image->rectTransform);
	questCount_Text->rectTransform->SetParent(quest_Image->rectTransform);
	quest_Image->rectTransform->SetPosition(800, 0);
	quest_Image->rectTransform->SetSize(250, 300);
	auto questImageTexture = ResourceManager::Get().CreateTexture2D("../Resource/mo/Quest.png");
	quest_Image->imageRenderer->sprite = ResourceManager::Get().CreateSprite(questImageTexture, "Quest");
	questName_Text->rectTransform->SetSize(300, 50);
	questName_Text->rectTransform->SetPosition(0, 50);
	questName_Text->screenTextRenderer->SetText(L"��ǥ");
	questName_Text->screenTextRenderer->SetFontSize(30);
	questName_Text->screenTextRenderer->SetFontName(L"���°���ü");
	quest_Text->rectTransform->SetPosition(0, -20);
	quest_Text->rectTransform->SetSize(200, 50);
	quest2_Text->rectTransform->SetPosition(0, -25);
	quest2_Text->rectTransform->SetSize(200, 50);
	quest3_Text->rectTransform->SetPosition(0, -50);
	quest3_Text->rectTransform->SetSize(200, 50);


	questCount_Text->rectTransform->SetPosition(0, -50);
	questCount_Text->rectTransform->SetSize(200, 0);
	quest = quest_Image->AddComponent<Quest>();


	// ��ȭâ UI
	chatNext_Image->rectTransform->SetParent(chat_Image->rectTransform);
	chat_Text->rectTransform->SetParent(chat_Image->rectTransform);
	chat_Button->rectTransform->SetParent(chat_Image->rectTransform);
	chat_Button->button->onClickListeners.AddListener(
		this, std::bind(&PlayUI::ClickChatButton, this));

	chat_Image->SetActive(false);
	chat_Image->rectTransform->SetPosition(0, -400);
	chat_Image->rectTransform->SetSize(800, 160);
	auto chatImageTexture = ResourceManager::Get().CreateTexture2D("../Resource/mo/Chat.png");
	chat_Image->imageRenderer->sprite = ResourceManager::Get().CreateSprite(chatImageTexture, "Chat");
	
	chatNext_Image->rectTransform->SetPosition(350, -40);
	chatNext_Image->rectTransform->SetSize(25, 22);
	auto nextImageTexture = ResourceManager::Get().CreateTexture2D("../Resource/mo/Next.png");
	chatNext_Image->imageRenderer->sprite = ResourceManager::Get().CreateSprite(nextImageTexture, "Next");


	chat_Text->rectTransform->SetSize(600, 50);
	chat_Text->screenTextRenderer->SetHorizontalAlign(TextHorizontalAlign::Left);
	chat_Text->screenTextRenderer->SetVerticalAlign(TextVerticalAlign::Top);

	chat = chat_Text->AddComponent<Chat>();
	chat_Button->rectTransform->SetPosition(240, -40);
	chat_Button->rectTransform->SetSize(184, 49);
	auto chatButtonTexture = ResourceManager::Get().CreateTexture2D("../Resource/mo/ChatButton.png");
	chat_Button->imageRenderer->sprite = ResourceManager::Get().CreateSprite(chatButtonTexture, "ChatButton");


	// ȥ & ��ų UI
	hon_Text->rectTransform->SetParent(hon_Image->rectTransform);
	skill1_Image->rectTransform->SetParent(hon_Image->rectTransform);
	skill2_Image->rectTransform->SetParent(hon_Image->rectTransform);

	// ȥ
	hon_Image->rectTransform->SetPosition(-850, -300);
	hon_Image->rectTransform->SetSize(70, 70);
	auto honImageTexture = ResourceManager::Get().CreateTexture2D("../Resource/mo/Hon.png");
	hon_Image->imageRenderer->sprite = ResourceManager::Get().CreateSprite(honImageTexture, "Hon");
	//hon_Image->imageRenderer->layer = 10;

	hon_Text->rectTransform->SetPosition(200, 0);
	hon_Text->rectTransform->SetSize(330, 50);
	hon_Text->screenTextRenderer->SetHorizontalAlign(TextHorizontalAlign::Left);
	hon_Text->screenTextRenderer->SetFontSize(40);

	hon_Text->screenTextRenderer->SetText(L"x 000") ;
	hon_Text->screenTextRenderer->SetFontName(L"���°���ü") ;

	// ��ų1
	skill1Key_Image->rectTransform->SetParent(skill1_Image->rectTransform);
	skill1Icon_Image->rectTransform->SetParent(skill1_Image->rectTransform);
	skill1CollTimeFilter_Image->rectTransform->SetParent(skill1_Image->rectTransform);

	skill1_Image->rectTransform->SetPosition(-3, -132);
	skill1_Image->rectTransform->SetSize(134.5, 120);
	auto skill1ImageTexture = ResourceManager::Get().CreateTexture2D("../Resource/mo/SkillQ_Activate.png");
	skill1_Image->imageRenderer->sprite = ResourceManager::Get().CreateSprite(skill1ImageTexture, "SkillQ_Activate");
	auto skillIconTexture = ResourceManager::Get().CreateTexture2D("../Resource/mo/SkillIcon.png");
	skill1Icon_Image->imageRenderer->sprite = ResourceManager::Get().CreateSprite(skillIconTexture, "SkillIcon");
	skill1Icon_Image->SetActive(false);

	skill1Key_Image->rectTransform->SetPosition(0, 50);
	skill1Key_Image->rectTransform->SetSize(50, 50);
	auto skill1KeyImageTexture = ResourceManager::Get().CreateTexture2D("../Resource/mo/Q.png");
	skill1Key_Image->imageRenderer->sprite = ResourceManager::Get().CreateSprite(skill1KeyImageTexture, "Q");
	

	auto skill1CollTimeFilterImageTexture = ResourceManager::Get().CreateTexture2D("../Resource/mo/SkillFilter.png");
	skill1CollTimeFilter_Image->imageRenderer->sprite = ResourceManager::Get().CreateSprite(skill1CollTimeFilterImageTexture, "SkillFilter");
	skill1CollTimeFilter_Image->imageRenderer->SetAlpha(0.4);
	skill1CollTimeFilter_Image->imageRenderer->fillType = FillType::Vertical;


	// ��ų2
	skill2Key_Image->rectTransform->SetParent(skill2_Image->rectTransform);
	skill2Icon_Image->rectTransform->SetParent(skill2_Image->rectTransform);

	skill2_Image->rectTransform->SetPosition(120, -132);
	skill2_Image->rectTransform->SetSize(100, 100);
	auto skill2ImageTexture = ResourceManager::Get().CreateTexture2D("../Resource/mo/SkillE_Deactivate.png");
	skill2_Image->imageRenderer->sprite = ResourceManager::Get().CreateSprite(skill2ImageTexture, "SkillE_Deactivate");
	skill2Icon_Image->imageRenderer->sprite = ResourceManager::Get().CreateSprite(skillIconTexture, "SkillIcon");

	skill2Key_Image->rectTransform->SetPosition(0, 50);
	skill2Key_Image->rectTransform->SetSize(50, 50);
	auto skill2KeyImageTexture = ResourceManager::Get().CreateTexture2D("../Resource/mo/E.png");
	skill2Key_Image->imageRenderer->sprite = ResourceManager::Get().CreateSprite(skill2KeyImageTexture, "E");

	skill2_Image->imageRenderer->renderMode = RenderMode::UnlitColorTint;
	skill2_Image->imageRenderer->SetColor(0.4, 0.4, 0.4);

	// ��ųâ UI

	skillWindowBackGroundGradient_Image->rectTransform->SetParent(skillWindowBackGround_Image->rectTransform);
	skillWindow_Image->rectTransform->SetParent(skillWindowBackGround_Image->rectTransform);
	skillWindowSplitter_Image->rectTransform->SetParent(skillWindowBackGround_Image->rectTransform);
	skillWindowClose_Button->rectTransform->SetParent(skillWindowBackGround_Image->rectTransform);
	for (auto& skillButton : skillButtons)
	{
		skillButton->rectTransform->SetParent(skillWindowBackGround_Image->rectTransform);
	}
	skillHonBig_Image->rectTransform->SetParent(skillWindowBackGround_Image->rectTransform);
	skillHon_Image->rectTransform->SetParent(skillWindowBackGround_Image->rectTransform);
	skillHon_Text->rectTransform->SetParent(skillHon_Image->rectTransform);
	skillWindowName_Image->rectTransform->SetParent(skillWindowBackGround_Image->rectTransform);

	skillWindowBackGround_Image->SetActive(false);
	skillWindowBackGround_Image->rectTransform->SetSize(1920, 1080);
	skillWindowBackGroundGradient_Image->rectTransform->SetSize(1920, 1080);

	skillWindowClose_Button->rectTransform->SetPosition(550, 280);
	skillWindowClose_Button->rectTransform->SetSize(83, 79);
	auto skillWindowClose_ButtonTexture = ResourceManager::Get().CreateTexture2D("../Resource/mo/BackButton.png");
	skillWindowClose_Button->imageRenderer->sprite = ResourceManager::Get().CreateSprite(skillWindowClose_ButtonTexture, "BackButton");
	//skillWindowClose_Button->imageRenderer->layer = 1;

	skillWindow_Image->rectTransform->SetSize(1248, 702);
	auto skillWindowImageTexture = ResourceManager::Get().CreateTexture2D("../Resource/mo/SkillWindow.png");
	skillWindow_Image->imageRenderer->sprite = ResourceManager::Get().CreateSprite(skillWindowImageTexture, "SkillWindow");
	skillWindowSplitter_Image->rectTransform->SetPosition(0, 70);
	skillWindowSplitter_Image->rectTransform->SetSize(700, 400);
	auto skillWindowSplitterImageTexture = ResourceManager::Get().CreateTexture2D("../Resource/mo/SkillWindowSplitter.png");
	skillWindowSplitter_Image->imageRenderer->sprite = ResourceManager::Get().CreateSprite(skillWindowSplitterImageTexture, "SkillWindowSplitter");
	auto skillWindowBackGroundImageTexture = ResourceManager::Get().CreateTexture2D("../Resource/mo/WindowBackGround.png");
	skillWindowBackGround_Image->imageRenderer->sprite = ResourceManager::Get().CreateSprite(skillWindowBackGroundImageTexture, "WindowBackGround");
	auto skillWindowBackGroundImageGradientTexture = ResourceManager::Get().CreateTexture2D("../Resource/mo/WindowBackGroundGradient.png");
	skillWindowBackGroundGradient_Image->imageRenderer->sprite = ResourceManager::Get().CreateSprite(skillWindowBackGroundImageGradientTexture, "WindowBackGroundGradient");

	for (int i = 0; i < skillButtons.size(); ++i)
	{
		std::string texturePath = "../Resource/mo/Skill" + std::to_string(i + 1) + ".png";
		std::string spriteName = "Skill" + std::to_string(i + 1);

		auto texture = ResourceManager::Get().CreateTexture2D(texturePath);
		skillButtons[i]->skillIcon_Button->imageRenderer->sprite = ResourceManager::Get().CreateSprite(texture, spriteName);
	}
	skillHon_Image->imageRenderer->sprite = ResourceManager::Get().CreateSprite(honImageTexture, "Hon");
	skillHonBig_Image->imageRenderer->sprite = ResourceManager::Get().CreateSprite(honImageTexture, "Hon");


	skillButtons[0]->rectTransform->SetPosition(-400, 160);
	skillButtons[1]->rectTransform->SetPosition(-400, -20);
	skillButtons[2]->rectTransform->SetPosition(-400, -200);
	skillButtons[3]->rectTransform->SetPosition(-50, 160);
	skillButtons[4]->rectTransform->SetPosition(-50, -20);
	skillButtons[5]->rectTransform->SetPosition(-50, -200);
	skillButtons[6]->rectTransform->SetPosition(300, 160);
	skillButtons[7]->rectTransform->SetPosition(300, -20);
	skillButtons[8]->rectTransform->SetPosition(300,-200);

	skillHonBig_Image->rectTransform->SetPosition(0,290);
	skillHonBig_Image->rectTransform->SetSize(50,50);
	skillHon_Image->rectTransform->SetPosition(480,-280);
	skillHon_Image->rectTransform->SetSize(30,30);
	//skillHon_Image->imageRenderer->layer = 10;
	skillHon_Text->rectTransform->SetPosition(120,0);
	skillHon_Text->rectTransform->SetSize(200,35);
	skillHon_Text->screenTextRenderer->SetFontSize(25);
	skillHon_Text->screenTextRenderer->SetHorizontalAlign(TextHorizontalAlign::Left);
	skillHon_Text->screenTextRenderer->SetText(L"x 000");
	skillHon_Text->screenTextRenderer->SetFontName(L"���°���ü");
	skillHon_Image->imageRenderer->layer = 1;
	skillHon_Text->screenTextRenderer->layer = 1;


	// ��ųâ ����
	skillWindowName_Image->rectTransform->SetPosition(0, 350);
	skillWindowName_Image->rectTransform->SetSize(273, 74);
	auto SkillWindowNameGradientTexture = ResourceManager::Get().CreateTexture2D("../Resource/mo/SkillWindowName.png");
	skillWindowName_Image->imageRenderer->sprite = ResourceManager::Get().CreateSprite(SkillWindowNameGradientTexture, "SkillWindowName");
	skillWindowName_Image->imageRenderer->layer = 1;
	
	for (UI_Button* btn : pauseCheckButtos)
	{
		btn->button->onClickListeners.AddListener(
			this, std::bind(&PlayUI::CheckPauseUI, this));
	}
	tooltipName = { L"index",L"Ignis",L"Dark",L"Luna",L"Nox"};

	chat_Button->button->onPointEnterListeners.AddListener(
		this, [this]() {
			chat_Button->imageRenderer->SetAlpha(1);
			auto chatButtonPressedTexture = ResourceManager::Get().CreateTexture2D("../Resource/mo/ChatButton_pressed.png");
			chat_Button->imageRenderer->sprite = ResourceManager::Get().CreateSprite(chatButtonPressedTexture, "ChatButtonPress");
		});

	chat_Button->button->onPointExitListeners.AddListener(
		this, [this]() {
				auto chatButtonTexture = ResourceManager::Get().CreateTexture2D("../Resource/mo/ChatButton.png");
				chat_Button->imageRenderer->sprite = ResourceManager::Get().CreateSprite(chatButtonTexture, "ChatButton");
		});

	stop_Button->button->onPointEnterListeners.AddListener(
		this, []() {
			GameManager::Get().canUseMouse = false;
		});

	stop_Button->button->onPointExitListeners.AddListener(
		this, [this]() {
			if(!pauseWindow->IsActive())
				GameManager::Get().canUseMouse = true;
		});

	skillWindowClose_Button->button->onClickListeners.AddListener(
		this, [this]() {
			skillWindowBackGround_Image->SetActive(false);
			GameManager::Get().canUseMouse = true;
			ButtonClickSound();
		});

	/*fail_Button->button->onClickListeners.AddListener(
		this, [this]() {
			/*skillWindowBackGround_Image->SetActive(false);
			pauseWindow->SetActive(false);
			stop_Button->SetActive(true);
			fail_Text->SetActive(false);
			fail_Button->SetActive(false);
			auto a = GameManager::Get().waveTime;
			fail_Text->screenTextRenderer->SetText(L"");
			BossReTry();
			ButtonClickSound();
			fade->FadeIn();
		}); */
}

void PlayUI::Update()
{
	if (GameManager::Get().isWave)
	{
		std::wstring timeText = (GameManager::Get().waveTime < 9 ? L"0" : L"") + std::to_wstring(static_cast<int>(std::ceil(GameManager::Get().waveTime)));
		timer_Text->screenTextRenderer->SetText(timeText);
	}

	if (!GameManager::Get().canUseAbsorb)
	{
		float cooltime = (GameManager::Get().absorbCoolTime) / (10 - GameManager::Get().GetSkillBonus(SkillType::SkillCooldownDown));
		skill1CollTimeFilter_Image->imageRenderer->fillAmount = cooltime;
	}

	if (waveInfo_Image->IsActive())
	{
		if (waveInfoTimer < waveIntoTime)
		{
			waveInfoTimer += Time::GetDeltaTime();

			float alpha = 1.0f;

			if (waveInfoTimer < fadeTime) // ���̵� �� ����
			{
				alpha = waveInfoTimer / fadeTime;
			}
			else if (waveInfoTimer > (waveIntoTime - fadeTime)) // ���̵� �ƿ� ����
			{
				alpha = (waveIntoTime - waveInfoTimer) / fadeTime;
			}
			else // ���� 1 ���� ����
			{
				alpha = 1.0f;
			}

			// clamp ���İ� (0 ~ 1)
			alpha = std::max(0.0f, std::min(1.0f, alpha));
			waveInfo_Image->imageRenderer->SetAlpha(alpha);
		}
		else
		{
			waveInfoTimer = 0;
			waveInfo_Image->imageRenderer->SetAlpha(0);
			waveInfo_Image->SetActive(false);
		}
	}

	if (tooltip1->IsActive())
	{
		if (tooltipInfoTimer < tooltipInfoTime)
		{
			tooltipInfoTimer += Time::GetDeltaTime();

			float alpha = 1.0f;

			if (tooltipInfoTimer < fadeTime) // ���̵� ��
			{
				alpha = tooltipInfoTimer / fadeTime;
			}
			else if (tooltipInfoTimer > (tooltipInfoTime - fadeTime)) // ���̵� �ƿ�
			{
				alpha = (tooltipInfoTime - tooltipInfoTimer) / fadeTime;
			}
			else // ���� 1 ����
			{
				alpha = 1.0f;
			}

			alpha = std::max(0.0f, std::min(1.0f, alpha));
			tooltip1->tooltipBackGround_Image->imageRenderer->SetAlpha(alpha);
			if (tooltip2->IsActive()) tooltip2->tooltipBackGround_Image->imageRenderer->SetAlpha(alpha);
		}
		else
		{
			tooltipInfoTimer = 0;
			tooltip1->tooltipBackGround_Image->imageRenderer->SetAlpha(0);
			tooltip1->SetActive(false);
			if (tooltip2->IsActive())
			{
				tooltip2->tooltipBackGround_Image->imageRenderer->SetAlpha(0);
				tooltip2->SetActive(false);
			}
		}
	}

	if (chat_Image->IsActive() && !chat_Button->IsActive())
	{
		// ���� ��ġ
		Vector2 curPos = chatNext_Image->rectTransform->GetPosition();

		float offsetY = sinf(Time::GetTotalTime() * 3.0f) * 0.5f;

		chatNext_Image->rectTransform->SetPosition(
			curPos.x,
			curPos.y + offsetY
		);
	}

	if (Input::GetKeyDown(VK_ESCAPE))
	{
		if (!skillWindowBackGround_Image->IsActive())
		{
			// Pause ���
			bool pauseActive = pauseWindow->IsActive();
			pauseWindow->SetActive(!pauseActive);
			skillWindowBackGround_Image->SetActive(false);
			Time::SetTimeScale(pauseActive ? 1 : 0);
			GameManager::Get().canUseMouse = chat_Image->IsActive() ? false : pauseActive;
		}
		else
		{
			// ��ų â �ݱ�
			GameManager::Get().canUseMouse = true;
			skillWindowBackGround_Image->SetActive(false);
		}
	}

	if (Input::GetKeyDown(VK_TAB))
	{
		if (pauseWindow->IsActive() || chat_Image->IsActive())
			return;

		bool skillActive = skillWindowBackGround_Image->IsActive();
		skillWindowBackGround_Image->SetActive(!skillActive);
		GameManager::Get().canUseMouse = skillActive;
	}


	if (Input::GetKeyDown(VK_F1))
	{
		GameManager::Get().questIndex = 2;
		GameManager::Get().waveCount = 0; 
		GameManager::Get().isQuest = false;
		GameManager::Get().questState = ChatCondition::Wave;
		GameManager::Get().canUseMouse = true;
		GameManager::Get().isWave = false;
		chat->SetSequenceCount(2);
		chat->SetCondition();
	}

	if (Input::GetKeyDown(VK_F2))
	{
		GameManager::Get().questIndex = 4;
		GameManager::Get().waveCount = 1;
		GameManager::Get().isQuest = false;
		GameManager::Get().questState = ChatCondition::Wave;
		GameManager::Get().canUseMouse = true;
		GameManager::Get().isWave = false;
		chat->SetSequenceCount(4);
		chat->SetCondition();
		
	}

	if (Input::GetKeyDown(VK_F3))
	{
		GameManager::Get().questIndex = 6;
		GameManager::Get().waveCount = 2;
		GameManager::Get().isQuest = false;
		GameManager::Get().questState = ChatCondition::Wave;
		GameManager::Get().canUseMouse = true;
		GameManager::Get().isWave = false;
		chat->SetSequenceCount(6);
		chat->SetCondition();
	}

	if (Input::GetKeyDown(VK_F4))
	{
		BossReTry();
	}

	if (Input::GetKeyDown(VK_F5))
	{
		GameManager::Get().AllSkillUnlock();
	}

	if (Input::GetKeyDown(VK_F6))
	{
		GameManager::Get().SkillReset();
	}

	if (Input::GetKeyDown(VK_F7))
	{
		GameManager::Get().ChangeHonCount(1180);
	}

	if (Input::GetKeyDown(VK_F8))
	{
		auto boss = GameObject::Find("Boss");
		if(boss)
			boss->GetComponent<BossController>()->TakeDamage(5);
	}

}

void PlayUI::Destroyed()
{

}

void PlayUI::ClickChatButton() {

	if (chat->GetChatCondition() == ChatCondition::Wave)
	{
		if(GameManager::Get().waveCount== 3)
		{
			GameObject::Find("MoonShadow")->GetComponent<MoonShadowController>()->DirectingBossWave();
			GameObject::Find("InGameCamera")->GetComponent<CameraController>()->ZoomOutFromPlayer();
			chat_Button->SetActive(false);
			chat_Image->SetActive(false);
			return;
		}
		WaveStartData();
	}
	else 
	{
		if (GameManager::Get().waveCount == 4 )
		{
			fade->FadeOut();
			InvokeSystem::Invoke(2.0f, []() {
				SceneManager::Get().ChangeScene(EclipseApp::END);
				});
			return;
		}
		GameManager::Get().questIndex++;
		chat_Button->SetActive(false);
		chat_Image->SetActive(false);
		GameManager::Get().canUseMouse = true;
		if(GameManager::Get().questIndex<3)GameManager::Get().isQuest = true;
		quest->RefreshQuestText();
		quest->RefreshQuestCountText(-1);
		bool check = skill1Icon_Image->IsActive();
		hon_Image->SetActive(true);
		skill1Icon_Image->SetActive(check);
		stop_Button->SetActive(true);
		quest_Image->SetActive(true);
		GameObject::Find("InGameCamera")->GetComponent<CameraController>()->ZoomOutFromPlayer();
		chat->SetCondition();
	}
}

void PlayUI::BossIntroEnd()
{
	bossHP->SetActive(true);
	WaveStartData();
}

void PlayUI::WaveStartData()
{
	GameManager::Get().questIndex++;
	GameManager::Get().WaveStart();
	chat_Button->SetActive(false);
	chat_Image->SetActive(false);
	GameManager::Get().canUseMouse = true;
	StartWaveInfo(GameManager::Get().waveCount);
	quest->RefreshQuestText();
	quest->RefreshQuestCountText(0);
	questCount_Text->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::White));
	if (skillWindowBackGround_Image->IsActive()) skillWindowBackGround_Image->SetActive(false);
	bool check = skill1Icon_Image->IsActive();
	hon_Image->SetActive(true);
	skill1Icon_Image->SetActive(check);
	stop_Button->SetActive(true);
	quest_Image->SetActive(true); 
	timer_Text->SetActive(true);
	timer_Image->SetActive(true);
	GameObject::Find("InGameCamera")->GetComponent<CameraController>()->ZoomOutFromPlayer();
}

void PlayUI::StartWaveInfo(int waveNumber)
{
	std::string stageImagePath;
	if (waveNumber < 4)
	{
		stageImagePath = "../Resource/mo/Stage0" + std::to_string(waveNumber) + ".png";
		bgmSource->SetClip(bgmClip_Wave);
	}
	else
	{
		stageImagePath = "../Resource/mo/Stage04.png"; // Boss Stage
		bgmSource->SetClip(bgmClip_Boss);
	}

	// Texture/Sprite ���� �� ����
	auto texture = ResourceManager::Get().CreateTexture2D(stageImagePath);
	waveInfo_Image->imageRenderer->sprite = ResourceManager::Get().CreateSprite(texture, "Stage" + std::to_string(waveNumber));

	waveInfoTimer = 0;
	waveInfo_Image->SetActive(true);
	waveInfo_Image->imageRenderer->SetAlpha(0);

	tooltipInfoTimer = 0;

	tooltip1->SetActive(true);
	tooltip1->ChangeInfo(tooltipName[waveNumber]);
	tooltip1->tooltipBackGround_Image->imageRenderer->SetAlpha(0);

	if (waveNumber == 1)
	{
		tooltip2->SetActive(true);
		tooltip2->ChangeInfo(L"Umbra");
		tooltip2->tooltipBackGround_Image->imageRenderer->SetAlpha(0);
	}
	bgmSource->Play();
}

void PlayUI::AllSkillCheat()
{
	for (auto& skillButton : skillButtons)
	{
		skillButton->skillIcon_Button->imageRenderer->renderMode = RenderMode::Unlit;
		skillButton->RefreshCurrentLevelText();
		skillButton->RefreshLevelUPHonCountText();
	}
}

void PlayUI::ResetAllSkillCheat()
{
	for (auto& skillButton : skillButtons)
	{
		skillButton->skillIcon_Button->imageRenderer->renderMode = RenderMode::UnlitColorTint;
		skillButton->RefreshCurrentLevelText();
		skillButton->RefreshLevelUPHonCountText();
	}
}

void PlayUI::PlayerInteraction()
{
	if (chat_Image->IsActive())
	{
		chat->NextChat();
	}
}

// ȥ ���� �߰� ȣ�� �Լ�
void PlayUI::ChangeHonCountText()
{
	int count = GameManager::Get().honCount;

	std::wstringstream ss;
	ss << L"x " << std::setw(3) << std::setfill(L'0') << count;

	hon_Text->screenTextRenderer->SetText(ss.str());
	skillHon_Text->screenTextRenderer->SetText(ss.str());
}

void PlayUI::ActivateAbsorb()
{
	skill1CollTimeFilter_Image->SetActive(false);
	skill1_Image->rectTransform->SetSize(134.5, 120);
	skill1_Image->rectTransform->SetPosition(-3, -132);
	auto skill1ImageTexture = ResourceManager::Get().CreateTexture2D("../Resource/mo/SkillQ_Activate.png");
	skill1_Image->imageRenderer->sprite = ResourceManager::Get().CreateSprite(skill1ImageTexture, "SkillQ_Activate");
	skill1Icon_Image->SetActive(false);
}

void PlayUI::DeactivateAbsorb()
{
	skill1CollTimeFilter_Image->SetActive(true);
	skill1_Image->rectTransform->SetSize(100, 100);
	skill1_Image->rectTransform->SetPosition(0, -132);
	auto skill1ImageTexture = ResourceManager::Get().CreateTexture2D("../Resource/mo/SkillQ_Deactivate.png");
	skill1_Image->imageRenderer->sprite = ResourceManager::Get().CreateSprite(skill1ImageTexture, "SkillQ_Deactivate");
	skill1Icon_Image->SetActive(true);
}

void PlayUI::ActivateRelease()
{
	skill2_Image->imageRenderer->renderMode = RenderMode::Unlit;
	//skill2_Image->rectTransform->SetPosition(117, -132);
	skill2_Image->rectTransform->SetSize(134.5, 120);
	auto skill2ImageTexture = ResourceManager::Get().CreateTexture2D("../Resource/mo/SkillE_Activate.png");
	skill2_Image->imageRenderer->sprite = ResourceManager::Get().CreateSprite(skill2ImageTexture, "SkillE_Activate");
	skill2Icon_Image->SetActive(false);
}

void PlayUI::DeactivateRelease()
{
	skill2_Image->imageRenderer->renderMode = RenderMode::UnlitColorTint; 
	//skill2_Image->rectTransform->SetPosition(120, -132);
	skill2_Image->rectTransform->SetSize(100, 100);
	auto skill2ImageTexture = ResourceManager::Get().CreateTexture2D("../Resource/mo/SkillE_Deactivate.png");
	skill2_Image->imageRenderer->sprite = ResourceManager::Get().CreateSprite(skill2ImageTexture, "SkillE_Deactivate");
	skill2Icon_Image->SetActive(true);
}

void PlayUI::CheckPauseUI()
{
	bool check = !pauseWindow->IsActive();
	pauseWindow->SetActive(check);
	if (check)
	{
		Time::SetTimeScale(0);
		skillWindowBackGround_Image->SetActive(false);
		GameManager::Get().canUseMouse = false;
	}
	else
	{
		Time::SetTimeScale(1);
		GameManager::Get().canUseMouse = true;
	}
	ButtonClickSound();
}

void PlayUI::SkillActiveSound()
{
	sfxSource->SetClip(sfxClip_SkillActive);
	sfxSource->Play();
}

void PlayUI::ButtonEnterSound()
{
	sfxSource->SetClip(sfxClip_Button1);
	sfxSource->Play();
}

void PlayUI::ButtonClickSound()
{
	sfxSource->SetClip(sfxClip_Button2);
	sfxSource->Play();
}

void PlayUI::FailEvent()
{

	GameManager::Get().canUseMouse = false;
	fail_Text->SetActive(true);
	//fail_Button->SetActive(true);
	stop_Button->SetActive(true);

	fail_Text->GetComponent<Typer>()->SetTextRenderer(fail_Text->screenTextRenderer);
	fail_Text->GetComponent<Typer>()->SetAudioSource(fail_Text->GetComponent<AudioSource>());
	fail_Text->GetComponent<Typer>()->StartTyping(L"�� ���� ������ �ʾҴ�.");
	sfxSource->SetClip(sfxClip_GameOver);
	sfxSource->Play();
}

void PlayUI::SuccessEvent()
{
	GameManager::Get().canUseMouse = false;
	success_Text->SetActive(true);
	stop_Button->SetActive(false);

	success_Text->GetComponent<Typer>()->SetTextRenderer(success_Text->screenTextRenderer);
	success_Text->GetComponent<Typer>()->SetAudioSource(success_Text->GetComponent<AudioSource>());
	success_Text->GetComponent<Typer>()->StartTyping(L"�޺��� ���ƿԴ�.");
}

void PlayUI::BossReTry()
{
	GameManager::Get().questIndex = 8;
	GameManager::Get().waveCount = 3;
	GameManager::Get().isQuest = false;
	GameManager::Get().questState = ChatCondition::Wave;
	GameManager::Get().canUseMouse = true;
	GameManager::Get().isWave = false;
	chat->SetSequenceCount(8);
	chat->SetCondition();
	GameObject::Find("MoonShadow")->GetComponent<MoonShadowController>()->ReStart();
	GameManager::Get().g_playUI->questCount_Text->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::White));
}

void PlayUI::ClearSound()
{
	bgmSource->SetLoop(true);
	bgmSource->SetClip(bgmClip_Clear);
	bgmSource->Play();
}
