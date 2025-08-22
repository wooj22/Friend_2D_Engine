#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/UI_Button.h"
#include "../Direct2D_EngineLib/UI_Image.h"
#include"../Direct2D_EngineLib/UI_Text.h"
#include"../Direct2D_EngineLib/Input.h"
#include"../Direct2D_EngineLib/SceneManager.h"
#include"../Direct2D_EngineLib/Scene.h"
#include"../Direct2D_EngineLib/Time.h"
#include"GameManager.h"


class SkillWindowButton : public GameObject
{
private: 
	int maxSkillLevel = 1;		// ��ų �ִ� ����
	SkillType skillName;		// ��ų �̸�
	float colorPositionX = 0;
	bool isEnterButton = false;
	float glowtimer = 0;
	float glowspeed = 3.0f;

public:
	UI_Image* skillIcon_Image;				// ��ų ������ ���
	UI_Button* skillIcon_Button;			// ��ų ������ ��ư
	UI_Text* skillLevel_Text;				// ��ų ���� �ؽ�Ʈ
	UI_Text* skillName_Text;				// ��ų �̸� �ؽ�Ʈ
	UI_Text* skillDesc_Text;				// ��ų ���� �ؽ�Ʈ
	UI_Text* skillColor1_Text;				// ��ų ���� �� �÷�1 �ؽ�Ʈ
	UI_Text* skillColor2_Text;				// ��ų ���� �� �÷�2 �ؽ�Ʈ
	UI_Text* skillColor3_Text;				// ��ų ���� �� �÷�3 �ؽ�Ʈ
	UI_Text* skillLevelUpHonCount_Text;		// ��ų ������ ���

	SkillWindowButton(SkillType name);
	~SkillWindowButton() override {}

	void Awake() override {}
	void SceneStart() override;
	void Update() override;
	void Destroyed() override {}

	float GetWidthSize(D2D1_SIZE_F image, D2D1_SIZE_F text);
	std::wstring ToWString(float value);
	void OnClickSkillButton();
	void OnPointEnterButton();
	void OnPointExitButton();

	void RefreshCurrentLevelText();
	void RefreshLevelUPHonCountText();
};

