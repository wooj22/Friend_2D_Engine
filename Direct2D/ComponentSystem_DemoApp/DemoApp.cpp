#include "DemoApp.h"

/// Game Init
void DemoApp::Init()
{
	__super::Init();

	// camera
	mainCamera.SetSize(width, height);

	// matrix init
	Transform::SetCameraMatrix(mainCamera.transform.GetWorldMatrix());
	Transform::unityMatrix = D2D1::Matrix3x2F::Scale(1.0f, -1.0f) * Transform::unityMatrix *
		D2D1::Matrix3x2F::Translation(width / 2.0f, height / 2.0f);

	// game object init
	player = new GameObject;
	sr = player->AddComponent<SpriteRenderer>();
	sr->SetImage(L"../Resource/Cat.png");
}

/// Game Update
void DemoApp::Update()
{
	__super::Update();

	// camera move
	if (InputManager::Get().GetKey(VK_LEFT)) mainCamera.transform.AddPosition(-3, 0);
	if (InputManager::Get().GetKey(VK_RIGHT)) mainCamera.transform.AddPosition(3, 0);
	if (InputManager::Get().GetKey(VK_UP)) mainCamera.transform.AddPosition(0, 3);
	if (InputManager::Get().GetKey(VK_DOWN)) mainCamera.transform.AddPosition(0, -3);

	// camera 역행렬 update
	Transform::SetCameraMatrix(mainCamera.transform.GetWorldMatrix());
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