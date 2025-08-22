#include "EclipseApp.h"
#include "../Friend_2D_EngineLib/RectTransform.h"
#include "Moon_Scene.h"
#include "Yunmo_Scene.h"
#include "Aron_Scene.h"
#include "Woo_Scene.h"
#include "MenuScene.h"
#include "PlayScene.h"
#include "EndScene.h"

void EclipseApp::Init()
{
	gameManager.Init();
	__super::Init();

	// ���콺 �ڵ� �����ϸ� x
	SetProcessDPIAware();

	// cursor
	hCursor = LoadCursorFromFile(L"../Resource/cursor.cur");
	if (hCursor)
	{
		SetCursor(hCursor);
		SetClassLongPtr(GetActiveWindow(), GCLP_HCURSOR, (LONG_PTR)hCursor);
	}

	// matrix init
	Transform::unityMatrix =
		D2D1::Matrix3x2F::Scale(1.0f, -1.0f) * Transform::unityMatrix *
		D2D1::Matrix3x2F::Translation(width / 2.0f, height / 2.0f);
	RectTransform::unityMatrix =
		D2D1::Matrix3x2F::Scale(1.0f, -1.0f) * D2D1::Matrix3x2F::Translation(width / 2.0f, height / 2.0f);

	// scene init
	sceneManager.CreateScene<Moon_Scene>();
	sceneManager.CreateScene<Yunmo_Scene>();
	sceneManager.CreateScene<Aron_Scene>();
	sceneManager.CreateScene<Woo_Scene>();
	sceneManager.CreateScene<MenuScene>();
	sceneManager.CreateScene<PlayScene>();
	sceneManager.CreateScene<EndScene>();
	sceneManager.SetCurrentScene(MENU);
	sceneManager.Init();
}


void EclipseApp::UnInit()
{
	__super::UnInit();
	gameManager.UnInit();
}


void EclipseApp::MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	__super::MessageProc(hwnd, uMsg, wParam, lParam);

	// game�� Ȱ���� message ó��
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	case WM_SETCURSOR:
		SetCursor(hCursor);
	}
}