#pragma once
#include "../Direct2D_EngineLib/Scene.h"
#include "../Direct2D_EngineLib/Input.h"
#include "../Direct2D_EngineLib/Camera.h"
#include "../Direct2D_EngineLib/UI_Button.h"
#include "../Direct2D_EngineLib/UI_Image.h"
#include"../Direct2D_EngineLib/UI_Text.h"
#include "DemoApp.h"

class StartScene : public Scene
{
private:
	Camera* camera;
	UI_Image* backgroundImage;
	UI_Text* titleText;
	UI_Button* startButton;
	
public:
	StartScene() = default;
	~StartScene() = default;

	void Awake() override;
	void Start() override;
	void Update() override;
	void Exit() override;

private:
	void ChagnePlayScene();
};

