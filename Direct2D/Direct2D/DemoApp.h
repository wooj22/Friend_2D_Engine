#pragma once
#include "../Direct2D_EngineLib/GameApp.h"

class DemoApp : public GameApp
{
public:
	DemoApp(int inputWidth = 1920, int inputHeight = 1080) :
		GameApp(inputWidth, inputHeight) { };
	~DemoApp() override = default;

	void Init() override;
	void UnInitialize() override;
	void MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;
};

