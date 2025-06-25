#include "MenuScene.h"

void MenuScene::Awake()
{
	// camera init
	camera = DemoApp::mainCamera;
	camera->transform->SetPosition(0, 0);

	// menu scene game object
	// 현재 renderer는 추가한 순서대로 그려짐
	// 추후 UI가 마지막에 그려지도록 rendersystem을 수정하고,
	// bacground는 게임오브젝트로 구현해야함
	menuUIManager = CreateObject<MenuUIManager>();
	menuUIManager->backGroundImage = CreateObject<UI_Image>();

	cat = CreateObject<Cat>();
	fish = CreateObject<Fish>();

	menuUIManager->titleText = CreateObject<UI_Text>();
	menuUIManager->button1 = CreateObject<UI_Button>();
	menuUIManager->button2 = CreateObject<UI_Button>();
	
	// game object -> awake (component add)
	__super::Awake();
}

void MenuScene::Start() 
{
	// 부모관계 지정
	fish->transform->SetParent(cat->transform);

	// Button event 등록
	menuUIManager->button1->button->onClickListeners.AddListener(
		&cat, std::bind(&Cat::Button1Click, cat));
	menuUIManager->button1->button->onClickListeners.AddListener(
		&fish, std::bind(&Fish::Button1Click, fish));

	menuUIManager->button2->button->onClickListeners.AddListener(
		&cat, std::bind(&Cat::Button2Click, cat));
	menuUIManager->button2->button->onClickListeners.AddListener(
		&fish, std::bind(&Fish::Button2Click, fish));

	// game object -> start (init lojic)
	__super::Start();
}

void MenuScene::Update() 
{
	// camera move
	if (Input::GetKey(VK_LEFT)) camera->transform->AddPosition(-200 * Time::GetDeltaTime(), 0);
	if (Input::GetKey(VK_RIGHT)) camera->transform->AddPosition(200 * Time::GetDeltaTime(), 0);
	if (Input::GetKey(VK_UP)) camera->transform->AddPosition(0, 200 * Time::GetDeltaTime());
	if (Input::GetKey(VK_DOWN)) camera->transform->AddPosition(0, -200 * Time::GetDeltaTime());

	// camera 역행렬 update
	Transform::SetCameraMatrix(camera->transform->GetWorldMatrix());

	// game object -> update
	__super::Update();

	// scene change
	if (Input::GetKeyDown(VK_SPACE)) {
		SceneManager::Get().ChangeScene(DemoApp::SceneName::PLAY);
	}
}

void MenuScene::Exit()
{
	// game object -> destroy
	camera = nullptr;
	__super::Exit();
}