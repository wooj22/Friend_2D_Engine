#include "PlayScene.h"

void PlayScene::Awake()
{
	// camera init
	camera = DemoApp::mainCamera;
	camera->transform->SetPosition(0, 0);

	// menu scene game object
	sun = CreateObject<Sun>();
	earth = CreateObject<Earth>();
	moon = CreateObject<Moon>();

	// game object -> awake (component add)
	__super::Awake();
}

void PlayScene::Start()
{
	// 부모관계 지정
	earth->transform->SetParent(sun->transform);
	moon->transform->SetParent(earth->transform);

	// game object -> start (init lojic)
	__super::Start();
}

void PlayScene::Update()
{
	// camera move
	if (Input::GetKey(VK_LEFT)) camera->transform->AddPosition(-3, 0);
	if (Input::GetKey(VK_RIGHT)) camera->transform->AddPosition(3, 0);
	if (Input::GetKey(VK_UP)) camera->transform->AddPosition(0, 3);
	if (Input::GetKey(VK_DOWN)) camera->transform->AddPosition(0, -3);

	// camera 역행렬 update
	Transform::SetCameraMatrix(camera->transform->GetWorldMatrix());

	// game object -> update
	__super::Update();

	// scene change
	if (Input::GetKeyDown(VK_SPACE)) {
		SceneManager::Get().ChangeScene(DemoApp::SceneName::MENU);
	}
}

void PlayScene::Exit()
{
	// game object -> destroy
	camera = nullptr;
	__super::Exit();
}