#include "PlayScene.h"

void PlayScene::Awake()
{
	// camera init
	cam = CreateObject<GameObject>();
	cam->AddComponent<Transform>();
	cam->AddComponent<Camera>(1400, 800);
	cam->GetComponent<Camera>()->SetMainCamera(cam->GetComponent<Camera>());

	// create gameobject
	uiManager = CreateObject<PlayUIManager>();
	uiManager->titleText = CreateObject<UI_Text>();
	uiManager->adviceText = CreateObject<UI_Text>();
	uiManager->memoryInfoText = CreateObject<UI_Text>();
	uiManager->buttonInfoText = CreateObject<UI_Text>();
	uiManager->buttonInfo2Text = CreateObject<UI_Text>();
	uiManager->backButton = CreateObject<UI_Button>();
	uiManager->nextButton = CreateObject<UI_Button>();

	mapManager = CreateObject<MapManager>();
	mapManager->map1 = CreateObject<SkyBackground>();
	mapManager->map2 = CreateObject<SkyBackground>();
	mapManager->map3 = CreateObject<SkyBackground>();
	mapManager->cloud1 = CreateObject<Cloud>();
	mapManager->cloud2 = CreateObject<Cloud>();
	mapManager->cloud3 = CreateObject<Cloud>();
	mapManager->cloud4 = CreateObject<Cloud>();
	mapManager->cloud5 = CreateObject<Cloud>();

	Wall = CreateObject<GameObject>();
	Wall->AddComponent<Transform>();
	Wall->AddComponent<BoxCollider>();

	Wall->GetComponent<Transform>()->SetPosition(-100,0);
	Wall->GetComponent<BoxCollider>()->size = {10,300};

	isCatCreate = false;
}

void PlayScene::Start()
{
	// game object -> SceneStart()
	__super::Start();

	// button event add
	uiManager->backButton->button->onClickListeners.AddListener(
		this, std::bind(&PlayScene::ChagneBackScene, this));

	uiManager->nextButton->button->onClickListeners.AddListener(
		this, std::bind(&PlayScene::ChagneNectScene, this));
}

void PlayScene::Update()
{
	// game object -> Update()
	__super::Update();

	Wall->GetComponent<BoxCollider>()->DebugColliderDraw();

	if (!isCatCreate && Input::GetKeyDown(VK_SPACE))
	{
		catText = CreateObject<CatText>();
		player = CreateObject<Cat>();
		catText->transform->SetParent(player->transform);
		player->transform->SetParent(mapManager->cloud1->transform);

		isCatCreate = true;
	}

	// camera move
	if (Input::GetKey(VK_LEFT)) cam->GetComponent<Transform>()->Translate(-300 * Time::GetDeltaTime(), 0);
	if (Input::GetKey(VK_RIGHT)) cam->GetComponent<Transform>()->Translate(300 * Time::GetDeltaTime(), 0);
}

void PlayScene::Exit()
{
	// game object -> destroy()
	__super::Exit();
}

void PlayScene::ChagneBackScene()
{
	SceneManager::Get().ChangeScene(DemoApp::START);
}

void PlayScene::ChagneNectScene()
{
	SceneManager::Get().ChangeScene(DemoApp::COL_TEST);
}