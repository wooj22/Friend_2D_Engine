#include "MenuScene.h"

void MenuScene::Awake()
{
	// camera init
	camera = DemoApp::mainCamera;
	camera->transform->SetPosition(0, 0);

	// menu scene game object
	cat = CreateObject<Cat>();
	fish = CreateObject<Fish>();

	// game object -> awake (component add)
	__super::Awake();
}

void MenuScene::Start() 
{
	// 부모관계 지정
	fish->transform->SetParent(cat->transform);

	// game object -> start (init lojic)
	__super::Start();
}

void MenuScene::Update() 
{
	// camera move
	if (InputManager::Get().GetKey(VK_LEFT)) camera->transform->AddPosition(-3, 0);
	if (InputManager::Get().GetKey(VK_RIGHT)) camera->transform->AddPosition(3, 0);
	if (InputManager::Get().GetKey(VK_UP)) camera->transform->AddPosition(0, 3);
	if (InputManager::Get().GetKey(VK_DOWN)) camera->transform->AddPosition(0, -3);

	// camera 역행렬 update
	Transform::SetCameraMatrix(camera->transform->GetWorldMatrix());

	// game object -> update
	__super::Update();

	// scene change
	if (InputManager::Get().GetKeyDown(VK_SPACE)) {
		SceneManager::Get().ChangeScene(DemoApp::SceneName::PLAY);
	}
}

void MenuScene::Exit()
{
	// game object -> destroy
	camera = nullptr;
	__super::Exit();
}