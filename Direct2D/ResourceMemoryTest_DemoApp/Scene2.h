#pragma once
#include "../Direct2D_EngineLib/Scene.h"
#include "../Direct2D_EngineLib/Input.h"
#include "../Direct2D_EngineLib/Camera.h"
#include "DemoApp.h"
#include "Cat.h"
#include "../Direct2D_EngineLib/UI_Image.h"
#include "../Direct2D_EngineLib/UI_Text.h"
#include "../Direct2D_EngineLib/UI_Button.h"

/* 리소스 공유자원 메모리 테스트 씬 - 버튼 클릭*/
class Scene2 : public Scene
{
private:
	Camera* camera;
	UI_Image* titleBackground;
	UI_Text* titleText;
	UI_Text* adviceText;
	UI_Text* memoryUsageText;
	UI_Button* createButton;
	UI_Button* deleteButton;

public:
	Scene2() = default;
	~Scene2() = default;

	void Awake() override;
	void Start() override;
	void Update() override;
	void Exit() override;

private:
	// 리소스 과제용으로 만든	test 함수
	void Scene2ObjectCreate();
	void Scene2ObjectSetting();

	void CreateButtonClick();
	void DeleteButtonClick();
};

