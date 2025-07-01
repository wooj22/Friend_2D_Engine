#pragma once
#include "../Direct2D_EngineLib/Scene.h"
#include "../Direct2D_EngineLib/Input.h"
#include "../Direct2D_EngineLib/Camera.h"
#include "DemoApp.h"
#include "Cat.h"
#include"../Direct2D_EngineLib/UI_Image.h"
#include"../Direct2D_EngineLib/UI_Text.h"

class Scene1 : public Scene
{
private:
	// scene1 objects
	Camera* camera;
	UI_Image* titleBackground;
	UI_Text* titleText;
	UI_Text* adviceText;
	UI_Text* memoryUsageText;

public:
	Scene1() = default;
	~Scene1() = default;

	void Awake() override;
	void Start() override;
	void Update() override;
	void Exit() override;

private:
	// 리소스 과제용으로 만든	test 함수
	void ObjectCreateTest();
	void ObjectSetting();
};

