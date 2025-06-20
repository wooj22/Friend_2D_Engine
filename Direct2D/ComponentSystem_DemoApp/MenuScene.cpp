#include "MenuScene.h"

void MenuScene::Start() 
{
	// camera init
	camera = DemoApp::mainCamera;
	camera->transform->SetPosition(0, 0);

	// menu scene game object
	// cat
	cat = CreateObject<Cat>();

	// fish
	fish = CreateObject<Fish>();
	fish->transform = fish->AddComponent<Transform>();
	fish->sr = fish->AddComponent<SpriteRenderer>();

	fish->transform->SetParent(cat->transform);
	fish->transform->SetScale(0.3, 0.3);
	fish->transform->SetRotation(-60);
	fish->transform->SetPosition(300, 300);
	fish->sr->SetImage(L"../Resource/Fish.png");

	__super::Start();
}

void MenuScene::Update() 
{
	__super::Update();

	// camera move
	if (InputManager::Get().GetKey(VK_LEFT)) camera->transform->AddPosition(-3, 0);
	if (InputManager::Get().GetKey(VK_RIGHT)) camera->transform->AddPosition(3, 0);
	if (InputManager::Get().GetKey(VK_UP)) camera->transform->AddPosition(0, 3);
	if (InputManager::Get().GetKey(VK_DOWN)) camera->transform->AddPosition(0, -3);

	// camera ¿ªÇà·Ä update
	Transform::SetCameraMatrix(camera->transform->GetWorldMatrix());

	// game object update
	fish->transform->AddRotation(1);
}

void MenuScene::Exit()
{

	__super::Exit();
}