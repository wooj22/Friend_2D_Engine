#include "Scene1.h"

void Scene1::Awake()
{
	// camera init
	camera = DemoApp::mainCamera;
	camera->transform->SetPosition(0, 0);

	// create gameobject
	// 생성자 -> ComponentInit() -> Awake()
	cat = CreateObject<Cat>();
	text = CreateObject<UI_Text>();
}

void Scene1::Start()
{
	// game object -> SceneStartInit
	__super::Start();
	text->rectTransform->SetPosition(0, 400);
	text->rectTransform->SetSize(500, 80);
	text->screenTextRenderer->SetText(L"[1][2][3] key로 Animation 전환");
}

void Scene1::Update()
{
	// game object -> Update
	__super::Update();

	// camera move
	if (Input::GetKey(VK_LEFT)) camera->transform->AddPosition(-300 * Time::GetDeltaTime(), 0);
	if (Input::GetKey(VK_RIGHT)) camera->transform->AddPosition(300 * Time::GetDeltaTime(), 0);
	if (Input::GetKey(VK_UP)) camera->transform->AddPosition(0, 300 * Time::GetDeltaTime());
	if (Input::GetKey(VK_DOWN)) camera->transform->AddPosition(0, -300 * Time::GetDeltaTime());

	// camera 역행렬 update
	Transform::SetCameraMatrix(camera->transform->GetWorldMatrix());

	// scene change
	/*if (Input::GetKeyDown(VK_SPACE)) {
		SceneManager::Get().ChangeScene(DemoApp::SceneName::SCENE2);
	}*/
}

void Scene1::Exit()
{
	// game object -> destroy
	camera = nullptr;
	__super::Exit();
}