#include "DemoApp.h"

/// Game Init
void DemoApp::Init()
{
	__super::Init();

	// camera
	mainCamera = new Camera(width, height);
	mainCamera->transform = mainCamera->AddComponent<Transform>();

	// matrix init
	Transform::SetCameraMatrix(mainCamera->transform->GetWorldMatrix());
	Transform::unityMatrix = D2D1::Matrix3x2F::Scale(1.0f, -1.0f) * Transform::unityMatrix *
		D2D1::Matrix3x2F::Translation(width / 2.0f, height / 2.0f);

	// game object
	cat = new Cat;
	cat->transform = cat->AddComponent<Transform>();
	cat->sr = cat->AddComponent<SpriteRenderer>();
	cat->tr = cat->AddComponent<TextRenderer>();

	cat->transform->SetPosition(0, 0);
	cat->sr->SetImage(L"../Resource/Cat.png");
	cat->tr->SetText(L"I'm Cat!");
	cat->tr->SetColor(D2D1::ColorF(D2D1::ColorF::Yellow));
	cat->tr->SetLayout(300, 100);
	
	fish = new Fish;
	fish->transform = fish->AddComponent<Transform>();
	fish->sr = fish->AddComponent<SpriteRenderer>();

	fish->transform->SetParent(cat->transform);
	fish->transform->SetScale(0.3, 0.3);
	fish->transform->SetRotation(-60);
	fish->transform->SetPosition(300, 300);
	fish->sr->SetImage(L"../Resource/Fish.png");
}

/// Game Update
void DemoApp::Update()
{
	__super::Update();

	// camera move
	if (InputManager::Get().GetKey(VK_LEFT)) mainCamera->transform->AddPosition(-3, 0);
	if (InputManager::Get().GetKey(VK_RIGHT)) mainCamera->transform->AddPosition(3, 0);
	if (InputManager::Get().GetKey(VK_UP)) mainCamera->transform->AddPosition(0, 3);
	if (InputManager::Get().GetKey(VK_DOWN)) mainCamera->transform->AddPosition(0, -3);

	// camera 역행렬 update
	Transform::SetCameraMatrix(mainCamera->transform->GetWorldMatrix());

	// game udpate
	cat->transform->AddPosition(0, -1);
	fish->transform->AddRotation(1);

	// debug
	/*OutputDebugStringA("고양이 포지션 : ");
	string str1 = to_string(cat->transform->GetPosition().x) +
		", " + to_string(cat->transform->GetPosition().y);
	OutputDebugStringA(str1.c_str());
	OutputDebugStringA("\n");

	OutputDebugStringA("카메라 포지션 : ");
	string str2 = to_string(mainCamera->transform->GetPosition().x) +
		", " + to_string(mainCamera->transform->GetPosition().y);
	OutputDebugStringA(str2.c_str());
	OutputDebugStringA("\n");*/
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