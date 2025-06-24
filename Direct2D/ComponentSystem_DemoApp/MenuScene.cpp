#include "MenuScene.h"

void MenuScene::Awake()
{
	// camera init
	camera = DemoApp::mainCamera;
	camera->transform->SetPosition(0, 0);

	// menu scene game object
	cat = CreateObject<Cat>();
	fish = CreateObject<Fish>();
	startButton = CreateObject<UI_Button>();
	
	// game object -> awake (component add)
	__super::Awake();
}

void MenuScene::Start() 
{
	// 부모관계 지정
	fish->transform->SetParent(cat->transform);

	// event 등록
	startButton->imageRenderer->SetImage(L"../Resource/Cat.png");
	startButton->rectTransform->SetPosition(10, 0);
	startButton->rectTransform->SetSize(300, 100);
	std::string str = std::to_string(startButton->rectTransform->GetPosition().x);
	OutputDebugStringA(str.c_str());
	//startButton->button->onClickListeners.AddListener();

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