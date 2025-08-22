#pragma once
#include "../Friend_2D_EngineLib/GameObject.h"
#include "../Friend_2D_EngineLib/UI_Image.h"
#include "../Friend_2D_EngineLib/UI_Text.h"
#include "../Friend_2D_EngineLib/SceneManager.h"
#include "../Friend_2D_EngineLib/Scene.h"
#include <unordered_map>


// ���� ���� ����
struct tooltipText {
	std::wstring skillname = L"";				// ���� �̸�
	std::wstring skillDesc = L"";				// ���� ����

	tooltipText(

		std::wstring name = L"",
		std::wstring descriptions = L"")
		:
		skillname(name),
		skillDesc(descriptions)
	{
	}
};

class tooltip : public GameObject
{
public:
	UI_Image* tooltipBackGround_Image;
	UI_Image* tooltip_Image;
	UI_Text* tooltipName_Text;
	UI_Text* tooltipDescribe_Text;

	std::unordered_map<wstring, tooltipText> textInfo;

public:
	void Awake() override;
	void SceneStart() override;
	void Update() override;
	void Destroyed() override;

	void ChangeInfo(const std::wstring& name);
};
