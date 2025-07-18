#pragma once
#include "../Direct2D_EngineLib/Scene.h"
#include "../Direct2D_EngineLib/Input.h"
#include "../Direct2D_EngineLib/Camera.h"

#include "StartUIManager.h"
#include "DemoApp.h"

class StartScene : public Scene
{
private:
	GameObject* cam;
	StartUIManager* uiManager;
	
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

