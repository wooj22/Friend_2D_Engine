#pragma once
#include "../Direct2D_EngineLib/GameApp.h"
#include "../Direct2D_EngineLib/Camera.h"

class DemoApp : public GameApp
{
public:
	enum SceneName { SCENE1 };	// scene enum
	static Camera* mainCamera;

	DemoApp(int inputWidth, int inputHeight) : GameApp(inputWidth, inputHeight) {};
	~DemoApp() override = default;

	void Init() override;
	void UnInit() override;
	void MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;
};