#pragma once
#include "../Direct2D_EngineLib/GameApp.h"
#include "../Direct2D_EngineLib/Camera.h"

class DemoApp : public GameApp
{
private:
	// camera
	Camera mainCamera;

public:
	DemoApp(int inputWidth, int inputHeight) : GameApp(inputWidth, inputHeight) {};
	~DemoApp() override = default;

	void Init() override;
	void Update() override;
	void UnInit() override;
	void MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;
};

