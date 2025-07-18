#pragma once
#include "../Direct2D_EngineLib/GameApp.h"
#include "../Direct2D_EngineLib/Camera_Old.h"

class DemoApp : public GameApp
{
public:
	enum SceneName { START, PLAY, COL_TEST };	// scene enum
	static Camera_Old* mainCamera;

	DemoApp(int inputWidth, int inputHeight) 
		: GameApp(inputWidth, inputHeight) 	{ };
	~DemoApp() override { delete mainCamera; }

	void Init() override;
	void UnInit() override;
	void MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;
};