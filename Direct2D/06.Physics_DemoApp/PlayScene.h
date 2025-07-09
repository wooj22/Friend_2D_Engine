#pragma once
#include "../Direct2D_EngineLib/Scene.h"
#include "../Direct2D_EngineLib/Input.h"
#include "../Direct2D_EngineLib/Camera.h"
#include "../Direct2D_EngineLib/UI_Button.h"
#include "../Direct2D_EngineLib/UI_Image.h"
#include"../Direct2D_EngineLib/UI_Text.h"
#include "DemoApp.h"

#include "SkyBackground.h"
#include "Cat.h"

class PlayScene : public Scene
{
private:
	Camera* camera;
	UI_Text* adviceText;
	UI_Button* backButton;

	SkyBackground* backSprite1;
	Cat* player;

public:
	PlayScene() = default;
	~PlayScene() = default;

	void Awake() override;
	void Start() override;
	void Update() override;
	void Exit() override;

private:
	void ChagneStartScene();
};

