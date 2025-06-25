#pragma once
#include "../Direct2D_EngineLib/Scene.h"
#include "../Direct2D_EngineLib/Input.h"
#include "../Direct2D_EngineLib/Camera.h"
#include "DemoApp.h"
#include "Cat.h"
#include "Fish.h"
#include "MenuUIManager.h"

class MenuScene : public Scene
{
private:
	// menu scene objects
	Camera* camera;
	Cat* cat;
	Fish* fish;

	MenuUIManager* menuUIManager;

public:
	MenuScene() = default;
	~MenuScene() = default;

	void Awake() override;
	void Start() override;
	void Update() override;
	void Exit() override;
};