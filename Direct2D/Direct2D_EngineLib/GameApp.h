#pragma once
#include "D2DRenderer.h"
#include "Singleton.h"
#include "Windows.h"
#include "string"
using namespace std;

class GameApp
{
protected:
	// window
	HINSTANCE		hInstance;		// 실행중인 프로그램 인스턴스 핸들
	HWND			hWnd;			// 윈도우 핸들
	int				width;
	int				height;
	wstring			winClassName = L"woo";
	wstring			titleName = L"Direct 2D Project";
	string			modulePath;
	string			workingPath;

	// Direct2D Renderer
	D2DRenderer d2dRenderer;

public:
	bool isLoop = true;

	GameApp(int inputWidth = 1024, int inputHeight = 768) :
		width(inputWidth), height(inputHeight), hInstance(nullptr), hWnd(nullptr) { };
	virtual ~GameApp() = default;

	virtual void Init();
	virtual void Update();
	virtual void Render();
	void Loop();
	virtual void UnInit();
	virtual void MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

