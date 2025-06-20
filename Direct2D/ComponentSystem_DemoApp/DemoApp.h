#pragma once
#include "../Direct2D_EngineLib/GameApp.h"
#include "../Direct2D_EngineLib/Camera.h"
#include "Cat.h"
#include "Fish.h"

class DemoApp : public GameApp
{
public:
	enum SceneName { MENU, PLAY };	// scene enum
	static Camera* mainCamera;		// 전체 scene이 같이 쓸 카메라
	
	DemoApp(int inputWidth, int inputHeight) : GameApp(inputWidth, inputHeight) {};
	~DemoApp() override = default;

	void Init() override;
	void UnInit() override;
	void MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;
};