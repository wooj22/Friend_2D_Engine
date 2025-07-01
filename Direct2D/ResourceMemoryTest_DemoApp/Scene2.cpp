#include "Scene2.h"

void Scene2::Awake()
{
	// camera init
	camera = DemoApp::mainCamera;
	camera->transform->SetPosition(0, 0);

	// game object create

	// game object -> awake
	__super::Awake();
}

void Scene2::Start()
{
	// game object -> start
	__super::Start();
}

void Scene2::Update()
{
	// camera move
	if (Input::GetKey(VK_LEFT)) camera->transform->AddPosition(-300 * Time::GetDeltaTime(), 0);
	if (Input::GetKey(VK_RIGHT)) camera->transform->AddPosition(300 * Time::GetDeltaTime(), 0);
	if (Input::GetKey(VK_UP)) camera->transform->AddPosition(0, 300 * Time::GetDeltaTime());
	if (Input::GetKey(VK_DOWN)) camera->transform->AddPosition(0, -300 * Time::GetDeltaTime());

	// camera ¿ªÇà·Ä update
	Transform::SetCameraMatrix(camera->transform->GetWorldMatrix());

	// scene change
	if (Input::GetKeyDown(VK_SPACE)) {
		SceneManager::Get().ChangeScene(DemoApp::SceneName::SCENE1);
	}
}

void Scene2::Exit()
{
	// game object -> destroy
	camera = nullptr;
	__super::Exit();
}