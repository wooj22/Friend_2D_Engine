#include "DemoApp.h"
#include "MenuScene.h"
#include "PlayScene.h"

// static member init
Camera* DemoApp::mainCamera = nullptr;

/// Game Init
void DemoApp::Init()
{
	__super::Init();

	// main camera init
	mainCamera = new Camera(width, height);
	mainCamera->transform = mainCamera->AddComponent<Transform>();

	// matrix init
	Transform::SetCameraMatrix(mainCamera->transform->GetWorldMatrix());
	Transform::unityMatrix = 
		D2D1::Matrix3x2F::Scale(1.0f, -1.0f) * Transform::unityMatrix *
		D2D1::Matrix3x2F::Translation(width / 2.0f, height / 2.0f);

	/*RectTransform::unityMatrix = 
		D2D1::Matrix3x2F::Scale(1.0f, -1.0f) * RectTransform::unityMatrix *
		D2D1::Matrix3x2F::Translation(width / 2.0f, height / 2.0f);*/

	// scene init
	sceneManager.CreateScene<MenuScene>();
	sceneManager.CreateScene<PlayScene>();

	sceneManager.SetCurrentScene(MENU);
	sceneManager.Init();
}

/// Game Release
void DemoApp::UnInit()
{
	__super::UnInit();
}

/// 윈도우 프로시저 메시지 처리
void DemoApp::MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	__super::MessageProc(hwnd, uMsg, wParam, lParam);

	// game에 활용할 message 처리
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	}
}