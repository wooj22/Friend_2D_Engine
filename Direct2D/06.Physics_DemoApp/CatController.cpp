#include "CatController.h"
#include "../Direct2D_EngineLib/Transform.h"
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/AnimatorController.h"
#include "../Direct2D_EngineLib/Animator.h"
#include "../Direct2D_EngineLib/Input.h"
#include "../Direct2D_EngineLib/Time.h"
#include "../Direct2D_EngineLib/ResourceManager.h"

void CatController::OnEnable()
{
	tr = owner->GetComponent<Transform>();
	sr = owner->GetComponent<SpriteRenderer>();
	ac = owner->GetComponent<Animator>()->controller;

	tr->SetScale(3, 3);
}

void CatController::Awake()
{

}

void CatController::Start()
{

}

void CatController::Update()
{
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

}

void CatController::InputCheak()
{
	isW = Input::GetKey('W');
	isA = Input::GetKey('A');
	isS = Input::GetKey('S');
	isD = Input::GetKey('D');
	isShift = Input::GetKey(VK_SHIFT);
}