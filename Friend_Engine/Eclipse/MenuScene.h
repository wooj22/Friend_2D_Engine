#pragma once
#include "../Friend_2D_EngineLib/Scene.h"
#include "../Friend_2D_EngineLib/Input.h"
#include "../Friend_2D_EngineLib/Camera.h"
#include "../Friend_2D_EngineLib/UI_Text.h"

#include "EclipseApp.h"
#include "TitleUI.h"

class MenuScene : public Scene
{
private:
	GameObject* cam;
	UI_Text* title_text;
	TitleUI* titleUI;

public:
	MenuScene() = default;
	~MenuScene() = default;

	void Awake() override;
	void Start() override;
	void Update() override;
	void Exit() override;
};


