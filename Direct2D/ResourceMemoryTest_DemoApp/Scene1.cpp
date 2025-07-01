#include "Scene1.h"

void Scene1::Awake()
{
	// camera init
	camera = DemoApp::mainCamera;
	camera->transform->SetPosition(0, 0);

	Scene1ObjectCreate();

	// game object -> awake
	__super::Awake();

	Scene1ObjectSetting();
}

void Scene1::Start()
{
	// game object -> start
	__super::Start();
}

void Scene1::Update()
{
	// camera move
	if (Input::GetKey(VK_LEFT)) camera->transform->AddPosition(-300 * Time::GetDeltaTime(), 0);
	if (Input::GetKey(VK_RIGHT)) camera->transform->AddPosition(300 * Time::GetDeltaTime(), 0);
	if (Input::GetKey(VK_UP)) camera->transform->AddPosition(0, 300 * Time::GetDeltaTime());
	if (Input::GetKey(VK_DOWN)) camera->transform->AddPosition(0, -300 * Time::GetDeltaTime());

	// camera 开青纺 update
	Transform::SetCameraMatrix(camera->transform->GetWorldMatrix());

	// 苞力
	if (Input::GetKeyDown('N')) CreateObject<Cat>();
	if (Input::GetKeyDown('D')) TestCatPop();
	if (Input::GetKeyDown('T')) ResourceManager::Get().Trim();
	if (Input::GetKeyDown(VK_SHIFT)) 
		memoryUsageText->screenTextRenderer->SetText(ResourceManager::Get().GetMemoryUsageString());

	// scene change
	if (Input::GetKeyDown(VK_SPACE)) {
		SceneManager::Get().ChangeScene(DemoApp::SceneName::SCENE2);
	}
}

void Scene1::Exit()
{
	// game object -> destroy
	camera = nullptr;
	__super::Exit();
}

void Scene1::Scene1ObjectCreate() 
{
	titleBackground = CreateObject<UI_Image>();
	titleText = CreateObject<UI_Text>();
	adviceText = CreateObject<UI_Text>();
	memoryUsageText = CreateObject<UI_Text>();
}

void Scene1::Scene1ObjectSetting() 
{
	titleBackground->rectTransform->SetPosition(0, 400);
	titleBackground->rectTransform->SetSize(600, 100);
	
	titleText->rectTransform->SetPosition(0, 400);
	titleText->rectTransform->SetSize(600, 100);
	titleText->screenTextRenderer->SetText(L"Resource Memory Test");
	titleText->screenTextRenderer->SetFontSize(50);
	titleText->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::Black));

	adviceText->rectTransform->SetPosition(0, 300);
	adviceText->rectTransform->SetSize(600, 100);
	adviceText->screenTextRenderer->SetText(L"[N] 积己, [D] 昏力, [T] Trim, [Shift] 皋葛府 犬牢");

	memoryUsageText->rectTransform->SetPivot(0, 1);
	memoryUsageText->rectTransform->SetPosition(-640, 200);
	memoryUsageText->rectTransform->SetSize(600, 300);
}