#include "Scene1.h"
#include "CatAnimatorController.h"

void Scene1::Awake()
{
	// camera init
	camera = DemoApp::mainCamera;
	camera->transform->SetPosition(0, 0);

	// create gameobject
	// 생성자 -> ComponentInit() -> Awake()
	cat = CreateObject<Cat>();
	advice_text = CreateObject<UI_Text>();
	catSpeed_text = CreateObject<UI_Text>();
}

void Scene1::Start()
{
	// game object -> SceneStartInit
	__super::Start();

	advice_text->rectTransform->SetPosition(0, 400);
	advice_text->rectTransform->SetSize(800, 200);
	advice_text->screenTextRenderer->SetFontSize(25);
	advice_text->screenTextRenderer->SetText(L"Cat의 speed에 따라 Animation Transition (Idle, Walk, Run)\nWASD 이동/ Shift 달리기");

	catSpeed_text->rectTransform->SetPosition(0, 350);
	catSpeed_text->rectTransform->SetSize(500, 80);
	catSpeed_text->screenTextRenderer->SetFontSize(20);
	catSpeed_text->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::YellowGreen));
}

void Scene1::Update()
{
	// game object -> Update
	__super::Update();

	// camera move
	/*if (Input::GetKey(VK_LEFT)) camera->transform->AddPosition(-300 * Time::GetDeltaTime(), 0);
	if (Input::GetKey(VK_RIGHT)) camera->transform->AddPosition(300 * Time::GetDeltaTime(), 0);
	if (Input::GetKey(VK_UP)) camera->transform->AddPosition(0, 300 * Time::GetDeltaTime());
	if (Input::GetKey(VK_DOWN)) camera->transform->AddPosition(0, -300 * Time::GetDeltaTime());*/

	// camera 역행렬 update
	Transform::SetCameraMatrix(camera->transform->GetWorldMatrix());

	// create
	if (Input::GetKeyDown('I')) CreateObject<Cat>();

	// ui update
	float speed = cat->GetComponent<CatController>()->GetSpeed();
	catSpeed_text->screenTextRenderer->SetText(L"Speed : " + to_wstring(speed));

	// debug
	if (Input::GetKeyDown('T'))ResourceManager::Get().Trim();
	if (Input::GetKeyDown('R')) ResourceManager::Get().PrintMemoryUsage();
}

void Scene1::Exit()
{
	// game object -> destroy
	camera = nullptr;
	__super::Exit();
}