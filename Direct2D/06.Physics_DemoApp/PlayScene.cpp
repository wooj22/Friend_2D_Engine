#include "PlayScene.h"

void PlayScene::Awake()
{
	// camera init
	camera = DemoApp::mainCamera;
	camera->transform->SetPosition(0, 0);

	// create gameobject
	uiManager = CreateObject<PlayUIManager>();
	uiManager->titleText = CreateObject<UI_Text>();
	uiManager->adviceText = CreateObject<UI_Text>();
	uiManager->memoryInfoText = CreateObject<UI_Text>();
	uiManager->buttonInfoText = CreateObject<UI_Text>();
	uiManager->backButton = CreateObject<UI_Button>();

	mapManager = CreateObject<MapManager>();
	mapManager->map1 = CreateObject<SkyBackground>();
	mapManager->map2 = CreateObject<SkyBackground>();
	mapManager->map3 = CreateObject<SkyBackground>();
	mapManager->cloud1 = CreateObject<Cloud>();
	mapManager->cloud2 = CreateObject<Cloud>();
	mapManager->cloud3 = CreateObject<Cloud>();
	mapManager->cloud4 = CreateObject<Cloud>();
	mapManager->cloud5 = CreateObject<Cloud>();

	isCatCreate = false;
}

void PlayScene::Start()
{
	// game object -> SceneStart()
	__super::Start();

	// button event add
	uiManager->backButton->button->onClickListeners.AddListener(
		this, std::bind(&PlayScene::ChagneStartScene, this));
}

void PlayScene::Update()
{
	// game object -> Update()
	__super::Update();

	if (!isCatCreate && Input::GetKeyDown(VK_SPACE))
	{
		catText = CreateObject<CatText>();
		player = CreateObject<Cat>();
		catText->transform->SetParent(player->transform);

		isCatCreate = true;
	}

	// camera move
	if (Input::GetKey(VK_LEFT)) camera->transform->Translate(-300 * Time::GetDeltaTime(), 0);
	if (Input::GetKey(VK_RIGHT)) camera->transform->Translate(300 * Time::GetDeltaTime(), 0);

	// camera ¿ªÇà·Ä update
	Transform::SetCameraMatrix(camera->transform->GetWorldMatrix());
}

void PlayScene::Exit()
{
	// game object -> destroy()
	camera = nullptr;
	__super::Exit();
}

void PlayScene::ChagneStartScene()
{
	SceneManager::Get().ChangeScene(DemoApp::START);
}