#include "MenuScene.h"
#include <string>

void MenuScene::Awake()
{
	// camera init
	camera = DemoApp::mainCamera;
	camera->transform->SetPosition(0, 0);

	// scene object create (layer x, 생성순서대로 렌더링됨)
	background = CreateObject<MenuBackground>();
	fish = CreateObject<Fish>();
	cat = CreateObject<Cat>();
	menuUIManager = CreateObject<MenuUIManager>();
	menuUIManager->titleImage = CreateObject<UI_Image>();
	menuUIManager->titleText = CreateObject<UI_Text>();
	menuUIManager->button1 = CreateObject<UI_Button>();
	menuUIManager->button2 = CreateObject<UI_Button>();
	
	// game object -> awake
	__super::Awake();
}

void MenuScene::Start() 
{
	// 부모관계 지정
	fish->transform->SetParent(cat->transform);

	// Button event 등록
	menuUIManager->button1->button->onClickListeners.AddListener(
		cat->catController, std::bind(&CatController::Button1Click, cat->catController));
	menuUIManager->button1->button->onClickListeners.AddListener(
		fish, std::bind(&Fish::Button1Click, fish));

	menuUIManager->button2->button->onClickListeners.AddListener(
		cat->catController, std::bind(&CatController::Button2Click, cat->catController));
	menuUIManager->button2->button->onClickListeners.AddListener(
		fish, std::bind(&Fish::Button2Click, fish));

	// game object -> start
	__super::Start();
}

void MenuScene::Update() 
{
	// camera move
	if (Input::GetKey(VK_LEFT)) camera->transform->AddPosition(-300 * Time::GetDeltaTime(), 0);
	if (Input::GetKey(VK_RIGHT)) camera->transform->AddPosition(300 * Time::GetDeltaTime(), 0);
	if (Input::GetKey(VK_UP)) camera->transform->AddPosition(0, 300 * Time::GetDeltaTime());
	if (Input::GetKey(VK_DOWN)) camera->transform->AddPosition(0, -300 * Time::GetDeltaTime());

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