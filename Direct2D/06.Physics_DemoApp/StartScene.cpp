#include "StartScene.h"

void StartScene::Awake()
{
	// camera init
	camera = DemoApp::mainCamera;
	camera->transform->SetPosition(0, 0);

	// create gameobject
	uiManager = CreateObject<StartUIManager>();
	uiManager->backgroundImage = CreateObject<UI_Image>();
	uiManager->titleText = CreateObject<UI_Text>();
	uiManager->startButton = CreateObject<UI_Button>();
}

void StartScene::Start()
{
	// game object -> SceneStart()
	__super::Start();

	// button event
	uiManager->startButton->button->onClickListeners.AddListener(
		this, std::bind(&StartScene::ChagnePlayScene, this));
}

void StartScene::Update()
{
	// game object -> Update()
	__super::Update();

	// camera ¿ªÇà·Ä update
	Transform::SetCameraMatrix(camera->transform->GetWorldMatrix());
}

void StartScene::Exit()
{
	// game object -> destroy()
	camera = nullptr;
	__super::Exit();
}

void StartScene::ChagnePlayScene()
{
	SceneManager::Get().ChangeScene(DemoApp::PLAY);
}