#include "PlayScene.h"
#include "../Direct2D_EngineLib/Time.h"
#include "DemoApp.h"

void PlayScene::Awake()
{
	// camera init
	camera = DemoApp::mainCamera;
	camera->transform->SetPosition(0, 0);

	// create gameobject
	// 积己磊 -> ComponentInit() -> Awake()
	adviceText = CreateObject<UI_Text>();
	backButton = CreateObject<UI_Button>();
	backSprite1 = CreateObject<SkyBackground>();
	player = CreateObject<Cat>();
}

void PlayScene::Start()
{
	// game object -> SceneStartInit
	__super::Start();

	adviceText->rectTransform->SetPosition(0, 350);
	adviceText->rectTransform->SetSize(800, 200);
	adviceText->screenTextRenderer->SetFontSize(30);
	adviceText->screenTextRenderer->SetText(L"advide text");
	adviceText->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::LightPink));

	backButton->rectTransform->SetPivot(0, 1);
	backButton->rectTransform->SetPosition(-680, 380);
	backButton->rectTransform->SetSize(50, 50);
	backButton->imageRenderer->SetBaseColor(D2D1::ColorF(D2D1::ColorF::LightPink));
	backButton->screenTextRenderer->SetText(L"Back");
	backButton->screenTextRenderer->SetFontSize(20);
	backButton->button->onClickListeners.AddListener(
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