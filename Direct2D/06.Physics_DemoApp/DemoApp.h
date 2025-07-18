#pragma once
#include "../Direct2D_EngineLib/GameApp.h"

class DemoApp : public GameApp
{
public:
	enum SceneName { START, PLAY, COL_TEST };	// scene enum

	DemoApp(int inputWidth, int inputHeight) 
		: GameApp(inputWidth, inputHeight) 	{ };
	~DemoApp() override { }

	void Init() override;
	void UnInit() override;
	void MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;
};