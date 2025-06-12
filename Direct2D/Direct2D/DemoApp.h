#pragma once
#include "../Direct2D_EngineLib/GameApp.h"

class DemoApp : public GameApp
{
private:
	ComPtr<ID2D1Bitmap1> catImage;

public:
	DemoApp(int inputWidth = 1024, int inputHeight = 768) :
		GameApp(inputWidth, inputHeight) { };
	~DemoApp() override = default;

	void Init() override;
	void Update() override;
	void Render() override;
	void UnInit() override;
	void MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;
};

