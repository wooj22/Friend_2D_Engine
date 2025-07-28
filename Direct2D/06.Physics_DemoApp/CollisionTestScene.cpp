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

	// ray test
	if (Input::GetKeyDown('R'))
	{
		Ray ray;
		ray.origin = Vector2::zero;
		ray.direction = Vector2::up;

		RaycastHit rayCast = ColliderSystem::Get().Raycast(ray, 10000);

		if (rayCast.collider)
		{
			std::wstring debugStr = L"[Raycast Hit]\n";
			debugStr += L"Hit Point: (" + std::to_wstring(rayCast.point.x) + L", " + std::to_wstring(rayCast.point.y) + L")\n";
			debugStr += L"Distance: " + std::to_wstring(rayCast.distance) + L"\n";

			// collider가 owner를 갖고 있고, owner가 GameObject이고, name을 string으로 가지고 있다고 가정
			GameObject* owner = rayCast.collider->gameObject;
			if (owner)
			{
				std::wstring nameW(owner->name.begin(), owner->name.end()); // string -> wstring
				debugStr += L"Collider Owner: " + nameW + L"\n";
				owner->Destroy();
			}

			OutputDebugString(debugStr.c_str());
		}
		else
		{
			OutputDebugString(L"[Raycast Miss]\n");
		}
	}
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