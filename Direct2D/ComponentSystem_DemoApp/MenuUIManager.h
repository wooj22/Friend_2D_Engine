#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/UI_Button.h"
#include "../Direct2D_EngineLib/UI_Image.h"
#include "../Direct2D_EngineLib/UI_Text.h"

class MenuUIManager : public GameObject
{
public:
	UI_Image* titleImage;
	UI_Text* titleText;
	UI_Button* button1;
	UI_Button* button2;

	void Awake() override;
	void Start() override;
	void Update() override;
	void Destroyed() override;
};

