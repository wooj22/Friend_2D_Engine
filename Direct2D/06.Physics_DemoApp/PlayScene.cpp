#include "PlayScene.h"

void PlayScene::Awake()
{
	// camera init
	camera = DemoApp::mainCamera;
	camera->transform->SetPosition(0, 0);

	// create gameobject
	// 积己磊 -> ComponentInit() -> Awake()
	uiManager = CreateObject<PlayUIManager>();
	uiManager->adviceText = CreateObject<UI_Text>();
	uiManager->backButton = CreateObject<UI_Button>();

	mapManager = CreateObject<MapManager>();
	mapManager->map1 = CreateObject<SkyBackground>();
	mapManager->map2 = CreateObject<SkyBackground>();
	mapManager->map3 = CreateObject<SkyBackground>();

	player = CreateObject<Cat>();
}

void PlayScene::Start()
{
	// game object -> SceneStartInit
	__super::Start();

	// button event add
	uiManager->backButton->button->onClickListeners.AddListener(
		this, std::bind(&PlayScene::ChagneStartScene, this));
}

void PlayScene::Update()
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

void PlayScene::Exit()
{
	// game object -> destroy
	camera = nullptr;
	__super::Exit();
}

void PlayScene::ChagneStartScene()
{
	SceneManager::Get().ChangeScene(DemoApp::START);
}