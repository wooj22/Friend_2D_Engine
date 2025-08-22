#pragma once
#include "../Friend_2D_EngineLib/UI_Button.h"
#include "../Friend_2D_EngineLib/UI_Image.h"
#include"../Friend_2D_EngineLib/UI_Text.h"
#include "../Friend_2D_EngineLib/GameObject.h"
#include "../Friend_2D_EngineLib/Singleton.h"
#include "../Friend_2D_EngineLib/Time.h"
#include "GameManager.h"
#include "SkillWindowButton.h"
#include "PauseWindow.h"
#include "BossHp.h"
#include "tooltip.h"
#include "MoonShadowController.h"
#include "CameraController.h"
#include "Typer.h"
#include "FadeManager.h"
#include "SoundManager.h"
#include "../Friend_2D_EngineLib/AudioSource.h"
#include <vector>

// ����
#include "../Friend_2D_EngineLib/AudioSystem.h"
#include "../Friend_2D_EngineLib/AudioSource.h"
#include "../Friend_2D_EngineLib/AudioClip.h"
#include "../Friend_2D_EngineLib/ResourceManager.h"

class Chat;
class Quest;
class NPC;


class PlayUI : public GameObject
{
private:
	float waveInfoTimer = 0;
	float waveIntoTime = 5;

	float tooltipInfoTimer = 0;
	float tooltipInfoTime = 10;

	float fadeTime = 2.5f;

	std::vector<wstring> tooltipName; 

	// audio
	shared_ptr<AudioClip> bgmClip_Main = nullptr;
	shared_ptr<AudioClip> bgmClip_Wave = nullptr;
	shared_ptr<AudioClip> bgmClip_Boss = nullptr;
	shared_ptr<AudioClip> bgmClip_Clear = nullptr;
	shared_ptr<AudioClip> sfxClip_Button1 = nullptr;
	shared_ptr<AudioClip> sfxClip_Button2 = nullptr;
	shared_ptr<AudioClip> sfxClip_SkillUI = nullptr;
	shared_ptr<AudioClip> sfxClip_SkillActive = nullptr;
	shared_ptr<AudioClip> sfxClip_GameOver = nullptr;
	shared_ptr<AudioClip> sfxClip_ChangeScene = nullptr;

	SoundManager* soundManager;

public:
	UI_Image* timer_Image;			// ���̺� Ÿ�̸� �̹���
	UI_Text* timer_Text;			// ���̺� Ÿ�̸� �ؽ�Ʈ

	UI_Button* stop_Button;			// �Ͻ� ���� ��ư
	PauseWindow* pauseWindow;
	std::vector<UI_Button*> pauseCheckButtos;

	UI_Image* skill_Tree;			// ��ų Ʈ�� �̹��� ���� ��ɿ� ���� ���� �ؾ���

	UI_Image* quest_Image;			// ����Ʈâ �̹���
	UI_Text* questName_Text;		// ����Ʈâ ����
	UI_Text* quest_Text;			// ����Ʈâ �ؽ�Ʈ
	UI_Text* quest2_Text;			// ����Ʈâ �ؽ�Ʈ
	UI_Text* quest3_Text;			// ����Ʈâ �ؽ�Ʈ
	UI_Text* questCount_Text;		// ����Ʈ �̼� ī��Ʈ �ؽ�Ʈ
	Quest* quest;					// ����Ʈ ��ũ��Ʈ

	UI_Image* chat_Image;			// ��ȭâ �̹���
	UI_Image* chatNext_Image;		// ��ȭâ next �̹���
	UI_Text* chat_Text;				// ��ȭâ �ؽ�Ʈ
	Typer* chatTyper;				// ��ȭâ Ÿ����
	AudioSource* chatAudioSource;	// ��ȭâ �����
	UI_Button* chat_Button;			// ����Ʈ ���� ��ư
	Chat* chat;						// ��ȭâ ��ũ��Ʈ

	UI_Image* hon_Image;			// ȥ �̹���
	UI_Text* hon_Text;				// ȥ ���� �ؽ�Ʈ

	UI_Image* skill1_Image;					//��ų1 �̹���
	UI_Image* skill1Icon_Image;				//��ų1 ������ �̹���
	UI_Image* skill1Key_Image;				//��ų1 �ؽ�Ʈ
	UI_Image* skill1CollTimeFilter_Image;	//��ų1 ������ �̹���

	UI_Image* skill2_Image;			// ��ų2 �̹���
	UI_Image* skill2Icon_Image;		// ��ų2 �̹���
	UI_Image* skill2Key_Image;		// ��ų1 �ؽ�Ʈ

	UI_Image* waveInfo_Image;		// ���̺� ���� �̹���

	tooltip* tooltip1;
	tooltip* tooltip2;

	UI_Button* skillWindowClose_Button;			// ��ų â ���� ȭ�� �̹���
	UI_Image* skillWindowBackGround_Image;			// ��ų â ���� ȭ�� �̹���
	UI_Image* skillWindowBackGroundGradient_Image;	// ��ų â �׶��̼� �̹���
	UI_Image* skillWindow_Image;					// ��ų â �̹���
	UI_Image* skillWindowSplitter_Image;			// ��ų â �̹���
	UI_Image* skillWindowName_Image;				// ��ųâ �̸� �̹���
	std::vector<SkillWindowButton*> skillButtons;	// ��ų ��ư ����
	UI_Image* skillHonBig_Image;					// ��ųâ ȥ �̹���
	UI_Image* skillHon_Image;						// ��ųâ ȥ �̹���
	UI_Text* skillHon_Text;							// ��ųâ ȥ ���� �ؽ�Ʈ

	BossHP* bossHP;
	NPC* npc;

	//Audio
	AudioSource* bgmSource = nullptr;
	AudioSource* sfxSource = nullptr;

	FadeManager* fade;
	UI_Text* success_Text;
	UI_Text* fail_Text;
	UI_Button* fail_Button;

	AudioSource* successAudioSource;
	AudioSource* failAudioSource;

public:
	// game object cycle
	PlayUI() : GameObject("PlayUI","PlayUI") {}
	~PlayUI() override {}

	// ������Ʈ�� ������ ��
	void Awake() override;
	// Scene�� Start (���� ��� ������Ʈ�� �����ǰ� �� ��)
	void SceneStart() override;
	// Scene�� Update
	void Update()  override;
	// Scene�� Exit, GameObject Delete
	void Destroyed() override;


	void ChangeHonCountText();

	void ActivateAbsorb();
	void DeactivateAbsorb();

	void ActivateRelease();

	void DeactivateRelease();

	void ChatSetActive(bool check) {
		chat_Image->SetActive(check);
		chat_Button->SetActive(false);
	}
	bool ChatActiveCheck() { return chat_Image->IsActive(); }
	void ClickChatButton();

	void BossIntroEnd();
	void WaveStartData();

	void AllSkillCheat();
	void ResetAllSkillCheat();
	void PlayerInteraction();

	void StartWaveInfo(int waveNumber);

	void CheckPauseUI();

	void SkillActiveSound();
	void ButtonEnterSound();
	void ButtonClickSound();

	void FailEvent();
	void SuccessEvent();
	void BossReTry();

	void ClearSound();
};
