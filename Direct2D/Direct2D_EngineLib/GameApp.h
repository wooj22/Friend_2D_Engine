#pragma once
#include "Windows.h"
#include "string"
#include "Singleton.h"
#include "GameObject.h"
#include "RenderSystem.h"
#include "TransformSystem.h"
#include "ButtonSystem.h"
#include "ScriptSystem.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Time.h"
#include "Input.h"

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

	// component system
	TransformSystem transformSystem;	// transform, rectTransfrom
	RenderSystem renderSystem;	// sprite, image, worldText, screenText
	ButtonSystem buttonSystem;	// button
	ScriptSystem scriptSystem;	// script

	// manager
	SceneManager sceneManager;
	ResourceManager resourceManager;

public:
	bool isLoop = true;

	GameApp(int inputWidth = 1024, int inputHeight = 768) :
		width(inputWidth), height(inputHeight), hInstance(nullptr), hWnd(nullptr) { };
	virtual ~GameApp() = default;

	/* Game Life Cycle */
	virtual void Init();
	void PreUpdate();		// input, time
	void Update();			// buttonsystem, transformSystem, scene(gameObject), scriptsystem
	void LateUpdate();		// renderSystem.update
	void Render();			// renderSystem.render
	void Loop();
	virtual void UnInit();

	virtual void MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

