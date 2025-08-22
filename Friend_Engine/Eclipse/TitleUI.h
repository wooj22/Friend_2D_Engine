#pragma once
#include "../Friend_2D_EngineLib/UI_Button.h"
#include "../Friend_2D_EngineLib/UI_Image.h"
#include"../Friend_2D_EngineLib/UI_Text.h"
#include "../Friend_2D_EngineLib/GameObject.h"
#include "../Friend_2D_EngineLib/SpriteRenderer.h"
#include "../Friend_2D_EngineLib/Animator.h"
#include "Options.h"
#include "Credit.h"
#include "LineClip.h"
#include "SoundManager.h"

// ����
#include "../Friend_2D_EngineLib/AudioSystem.h"
#include "../Friend_2D_EngineLib/AudioSource.h"
#include "../Friend_2D_EngineLib/AudioClip.h"
#include "../Friend_2D_EngineLib/ResourceManager.h"

class TitleUI : public GameObject
{
private:
	float glowtimer = 0;
	float glowspeed = 1.8f;
	SoundManager* soundManager;
public:
	GameObject* backgroundImage;
	GameObject* titleLogo_Image;
	GameObject* titleSpell_Image;

	UI_Button* play_Button;
	UI_Button* options_Button;
	UI_Button* credit_Button;
	UI_Button* end_Button;
	UI_Image* underscore_Image;
	std::vector<UI_Button*> menuButtons;
	std::vector<UI_Button*> optionButtons;

	Options* optionUI;
	Credit* creditUI;

	// hover event check
	UI_Button* prevHoverButton = nullptr;

	// audio
	AudioSource* bgmSource = nullptr;
	AudioSource* sfxSource = nullptr;
	shared_ptr<AudioClip> bgmClip = nullptr;
	shared_ptr<AudioClip> sfxClip_Button1 = nullptr;
	shared_ptr<AudioClip> sfxClip_Button2 = nullptr;
	shared_ptr<AudioClip> sfxClip_ChangeScene = nullptr;

	LineController* linecontroller;

public:
	// game object cycle
	TitleUI() {}
	~TitleUI() override {}

	// ������Ʈ�� ������ ��
	void Awake() override;

	// Scene�� Start (���� ��� ������Ʈ�� �����ǰ� �� ��)
	void SceneStart() override;

	// Scene�� Update
	void Update()  override;

	// Scene�� Exit, GameObject Delete
	void Destroyed() override;
	void OnPointEnterButton(UI_Button* parent);
	void OnPointExitButton(UI_Button* prevButton);
	void OnClickOptionUI(UI_Button* button);
	void OpenOptionUI();
	void OpenCreditUI();
	void ChangePlayScene();
};



