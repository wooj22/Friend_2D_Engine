#include "CatController.h"
#include "../Direct2D_EngineLib/Transform.h"
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/AnimatorController.h"
#include "../Direct2D_EngineLib/Animator.h"
#include "../Direct2D_EngineLib/Input.h"
#include "../Direct2D_EngineLib/Time.h"
#include "../Direct2D_EngineLib/ResourceManager.h"
#include "../Direct2D_EngineLib/WorldTextRenderer.h"

// 컴포넌트 활성화 시점
void CatController::OnEnable()
{
	OutputDebugStringA("CatController OnEnable()\n");
}

void CatController::Awake()
{
	OutputDebugStringA("CatController Awake()\n");

	tr = owner->GetComponent<Transform>();
	sr = owner->GetComponent<SpriteRenderer>();
	ac = owner->GetComponent<Animator>()->controller;

	infoText = GameObject::Find("CatText")->GetComponent<WorldTextRenderer>();
}

void CatController::Start()
{
	OutputDebugStringA("CatController Start()\n");
	tr->SetScale(3, 3);
}

void CatController::Update()
{
	// input
	InputCheak();

	// speed setting
	if (isW || isA || isS || isD) {
		if (!isShift) curSpeed = walkSpeed;
		else curSpeed = runSpeed;
	}
	else curSpeed = 0;

	// filp
	sr->flipX = Input::GetAxisHorizontal() >= 0 ? false : true;

	// animation
	ac->SetFloat("Speed", curSpeed);

	// ui
	InfoTextUpdate();
}

void CatController::FixedUpdate()
{
	// move
	float inputX = Input::GetAxisHorizontal();
	float inputY = Input::GetAxisVertical();
	Vector2 direction = Vector2(inputX, inputY).Normalized();
	tr->Translate(direction * curSpeed);
}

void CatController::OnDestroy()
{
	OutputDebugStringA("CatController OnDestroy()\n");
}

void CatController::InputCheak()
{
	isW = Input::GetKey('W');
	isA = Input::GetKey('A');
	isS = Input::GetKey('S');
	isD = Input::GetKey('D');
	isShift = Input::GetKey(VK_SHIFT);
}

void CatController::InfoTextUpdate()
{
	infoText->SetText(L"speed : " + to_wstring(curSpeed));
}