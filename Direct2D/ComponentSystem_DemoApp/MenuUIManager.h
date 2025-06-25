#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/UI_Button.h"

class MenuUIManager : public GameObject
{
public:
	UI_Button* button1;
	UI_Button* button2;

	void Awake() override;
	void Start() override;
	void Update() override;
	void Destroy() override;
};

