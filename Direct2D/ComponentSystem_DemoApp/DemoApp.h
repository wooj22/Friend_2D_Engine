#pragma once
#include "../Direct2D_EngineLib/GameApp.h"
#include "../Direct2D_EngineLib/Camera.h"
#include "Cat.h"
#include "Fish.h"

class DemoApp : public GameApp
{
private:
	// camera
	Camera* mainCamera;

	// game object
	Cat* cat;
	Fish* fish;

public:
	DemoApp(int inputWidth, int inputHeight) : GameApp(inputWidth, inputHeight) {};
	~DemoApp() override = default;

	void Init() override;
	void PreUpdate() override {};
	void Update() override;
	void LateUpdate() override {};
	void UnInit() override;
	void MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;
};

