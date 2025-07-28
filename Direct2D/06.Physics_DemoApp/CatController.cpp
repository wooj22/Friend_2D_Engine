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
#include "Cat.h"
#include "Cloud.h"

// 컴포넌트 활성화 시점
void CatController::OnEnable()
{

}

void CatController::Awake()
{
	tr = gameObject->GetComponent<Transform>();
	sr = gameObject->GetComponent<SpriteRenderer>();
	rb = gameObject->GetComponent<Rigidbody>();
	ac = gameObject->GetComponent<Animator>()->controller;

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
	if (isA || isD) {
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

	// instantiate test
	if (Input::GetKeyDown('3'))
	{
		Instantiate<Cat>({ 0,0 });
	}
	if (Input::GetKeyDown('4'))
	{
		Instantiate<Cloud>({ 0,0 });
	}

	// reset pos
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
	isD = Input::GetKey('D');
	isShift = Input::GetKey(VK_SHIFT);
	isSpace = Input::GetKeyDown(VK_SPACE);
}

// 일반 이동
void CatController::Move_Transform()
{
	Vector2 direction = Vector2(inputX, inputY).Normalized();
	tr->Translate(direction * curSpeed);
}

// 물리 이동
void CatController::Move_Physics()
{
	rb->velocity.x = inputX * curSpeed;
}

// 물리 점프
void CatController::Jump_Physics()
{
	if (isW && isGround)
	{
		rb->AddImpulse(Vector2(0, jumpForce));
	}
}

void CatController::InfoTextUpdate()
{
	//infoText->SetText(L"is Ground: " + to_wstring(isGround));
	infoText->SetText(L"rigidbody isGrounded : " + to_wstring(rb->isGrounded)
	+ L"\nvelocity y : " + to_wstring(rb->velocity.y)
    + L"\nblock y up : " + to_wstring(rb->isBlockedUp)
		+ L"\nblock y down : " + to_wstring(rb->isBlockedDown));
	//infoText->SetText(L"velocity y : " + to_wstring(rb->velocity.y));
}

