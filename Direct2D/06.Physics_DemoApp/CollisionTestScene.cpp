#include "CollisionTestScene.h"

void CollisionTestScene::Awake()
{
	// camera init
	cam = CreateObject<GameObject>();
	cam->AddComponent<Transform>();
	cam->AddComponent<Camera>(1400, 800);
	cam->GetComponent<Camera>()->SetMainCamera(cam->GetComponent<Camera>());

	// create gameobject
	uiManager = CreateObject<ColUIManager>();
	uiManager->titleText = CreateObject<UI_Text>();
	uiManager->infoText1 = CreateObject<UI_Text>();
	uiManager->infoText2 = CreateObject<UI_Text>();
	uiManager->backButton = CreateObject<UI_Button>();
	circle = CreateObject<CircleObject>();
	box = CreateObject<BoxObject>();
	circleText = CreateObject<ColObText>();
	boxText = CreateObject<ColObText>();

	// test
	parentOb = CreateObject<GameObject>();
	parentOb->AddComponent<Transform>();
	parentOb->GetComponent<Transform>()->SetPosition(-100,0);
	//box->transform->SetParent(parentOb->GetComponent<Transform>());
}

void CollisionTestScene::Start()
{
	// parent, init
	circleText->transform->SetParent(circle->transform);
	boxText->transform->SetParent(box->transform);

	circle->testScript->text = circleText->GetComponent<WorldTextRenderer>();
	box->testScript->text = boxText->GetComponent<WorldTextRenderer>();

	// button event add
	uiManager->backButton->button->onClickListeners.AddListener(
		this, std::bind(&CollisionTestScene::ChagneBackScene, this));

	// game object -> SceneStart()
	__super::Start();
}

void CollisionTestScene::Update()
{
	// game object -> Update()
	__super::Update();
}

void CollisionTestScene::Exit()
{
	// game object -> destroy()
	__super::Exit();
}

void CollisionTestScene::ChagneBackScene()
{
	SceneManager::Get().ChangeScene(DemoApp::PLAY);
}