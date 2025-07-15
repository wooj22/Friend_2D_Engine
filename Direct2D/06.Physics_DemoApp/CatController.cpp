#include "CatController.h"
#include "../Direct2D_EngineLib/Transform.h"
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/AnimatorController.h"
#include "../Direct2D_EngineLib/Animator.h"
#include "../Direct2D_EngineLib/Input.h"
#include "../Direct2D_EngineLib/Time.h"
#include "../Direct2D_EngineLib/ResourceManager.h"
#include "../Direct2D_EngineLib/WorldTextRenderer.h"
#include "../Direct2D_EngineLib/Rigidbody.h"

// 컴포넌트 활성화 시점
void CatController::OnEnable()
{

}

void CatController::Awake()
{
	tr = owner->GetComponent<Transform>();
	sr = owner->GetComponent<SpriteRenderer>();
	rb = owner->GetComponent<Rigidbody>();
	ac = owner->GetComponent<Animator>()->controller;

	infoText = GameObject::Find("CatText")->GetComponent<WorldTextRenderer>();
}

void CatController::Start()
{
	
}

void CatController::Update()
{
	// input
	InputCheak();

	// jump -> input이 update에서 update되고있기 때문에
	Jump_Physics();

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

	if (tr->GetPosition().y < -500.0f)
	{
		tr->SetPosition(0, 300);
		// Destory 
	}
}

void CatController::FixedUpdate()
{
	//Move_Transform();
	Move_Physics();
}

void CatController::OnDestroy()
{
	
}

void CatController::InputCheak()
{
	inputX = Input::GetAxisHorizontal();
	inputY = Input::GetAxisVertical();

	isW = Input::GetKey('W');
	isA = Input::GetKey('A');
	isS = Input::GetKey('S');
	isD = Input::GetKey('D');
	isShift = Input::GetKey(VK_SHIFT);
	isSpace = Input::GetKeyDown(VK_SPACE);
}

void CatController::Move_Transform()
{
	Vector2 direction = Vector2(inputX, inputY).Normalized();
	tr->Translate(direction * curSpeed);
}

void CatController::Move_Physics()
{
	Vector2 direction = Vector2(inputX, inputY).Normalized();
	rb->velocity = direction * curSpeed;
}

void CatController::Jump_Physics()
{
	if (isSpace)
	{
		rb->AddForce(Vector2(0, jumpForce));
	}
}


void CatController::InfoTextUpdate()
{
	infoText->SetText(L"speed : " + to_wstring(curSpeed));
}

