#pragma once
#include "../Direct2D_EngineLib/GameApp.h"

class DemoApp : public GameApp
{
private:
	BitmapRenderer sun;
	BitmapRenderer earth;
	BitmapRenderer moon;

public:
	DemoApp(int inputWidth, int inputHeight) : GameApp(inputWidth, inputHeight) { };
	~DemoApp() override = default;

	void Init() override;
	void Update() override;
	void UnInit() override;
	void MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;
};

