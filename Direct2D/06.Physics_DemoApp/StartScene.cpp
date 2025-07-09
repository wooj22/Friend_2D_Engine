#include "StartScene.h"

void StartScene::Awake()
{
	// camera init
	camera = DemoApp::mainCamera;
	camera->transform->SetPosition(0, 0);

	// create gameobject
	// 积己磊 -> ComponentInit() -> Awake()
	backgroundImage = CreateObject<UI_Image>();
	titleText = CreateObject<UI_Text>();
	startButton = CreateObject<UI_Button>();
}

void StartScene::Start()
{
	// game object -> SceneStartInit
	__super::Start();

	// background
	backgroundImage->rectTransform->SetPivot(0, 1);
	backgroundImage->rectTransform->SetPosition(-700, 400);
	backgroundImage->rectTransform->SetSize(1400, 800);
	auto sky = ResourceManager::Get().CreateTexture2D("../Resource/Sky.png");
	backgroundImage->imageRenderer->sprite = ResourceManager::Get().CreateSprite(sky, "Sky");
	//backgroundImage->imageRenderer->SetBaseColor(D2D1::ColorF(D2D1::ColorF::Coral));

	// text
	titleText->rectTransform->SetPosition(0, 80);
	titleText->rectTransform->SetSize(800, 200);
	titleText->screenTextRenderer->SetFontSize(60);
	titleText->screenTextRenderer->SetText(L"Flatformer DemoApp");
	titleText->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::LightPink));

	// button
	startButton->rectTransform->SetPosition(0, -50);
	startButton->rectTransform->SetSize(180, 70);
	startButton->imageRenderer->SetBaseColor(D2D1::ColorF(D2D1::ColorF::LightPink));
	startButton->screenTextRenderer->SetText(L"Start");
	startButton->screenTextRenderer->SetFontSize(30);
	startButton->button->onClickListeners.AddListener(
		this, std::bind(&StartScene::ChagnePlayScene, this));
}

void StartScene::Update()
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

void StartScene::Exit()
{
	// game object -> destroy
	camera = nullptr;
	__super::Exit();
}

void StartScene::ChagnePlayScene()
{
	SceneManager::Get().ChangeScene(DemoApp::PLAY);
}