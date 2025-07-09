#include "StartScene.h"

void StartScene::Awake()
{
	// camera init
	camera = DemoApp::mainCamera;
	camera->transform->SetPosition(0, 0);

	// create gameobject
	// 积己磊 -> ComponentInit() -> Awake()
	uiManager = CreateObject<StartUIManager>();
	uiManager->backgroundImage = CreateObject<UI_Image>();
	uiManager->titleText = CreateObject<UI_Text>();
	uiManager->startButton = CreateObject<UI_Button>();
}

void StartScene::Start()
{
	// game object -> SceneStartInit
	__super::Start();

	// button event
	uiManager->startButton->button->onClickListeners.AddListener(
		this, std::bind(&StartScene::ChagnePlayScene, this));
}

void StartScene::Update()
{
	// game object -> Update
	__super::Update();

	// camera move
	if (Input::GetKey(VK_LEFT)) camera->transform->Translate(-300 * Time::GetDeltaTime(), 0);
	if (Input::GetKey(VK_RIGHT)) camera->transform->Translate(300 * Time::GetDeltaTime(), 0);
	if (Input::GetKey(VK_UP)) camera->transform->Translate(0, 300 * Time::GetDeltaTime());
	if (Input::GetKey(VK_DOWN)) camera->transform->Translate(0, -300 * Time::GetDeltaTime());

	// camera 开青纺 update
	Transform::SetCameraMatrix(camera->transform->GetWorldMatrix());
}

void StartScene::Exit()
{
	// game object -> destroy
	camera = nullptr;
	__super::Exit();
}

void StartScene::ChagnePlayScene()
{
	SceneManager::Get().ChangeScene(DemoApp::PLAY);
}