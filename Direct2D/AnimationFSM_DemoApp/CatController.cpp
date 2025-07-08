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

void CatController::Update()
{
	InputCheak();

	// cat state
	if (isW || isA || isS || isD) {
		if (!isShift) {
			curSpeed = walkSpeed;
			Walk();
		}
		else {
			curSpeed = runSpeed;
			Run();
		}
	}
	else curSpeed = 0;

	// filp
	sr->flipX = Input::GetAxisHorizontal() >= 0 ? false : true;

	// animation
	ac->SetFloat("Speed", curSpeed);
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

void CatController::Walk()
{
	// TODO :: vector µµÀÔ
	if (isW) tr->AddPosition(0, curSpeed * Time::GetDeltaTime());
	if (isA) tr->AddPosition(-curSpeed * Time::GetDeltaTime(), 0);
	if (isS) tr->AddPosition(0, -curSpeed * Time::GetDeltaTime());
	if (isD) tr->AddPosition(curSpeed * Time::GetDeltaTime(), 0);
}

void CatController::Run()
{
	if (isW) tr->AddPosition(0, curSpeed * Time::GetDeltaTime());
	if (isA) tr->AddPosition(-curSpeed * Time::GetDeltaTime(), 0);
	if (isS) tr->AddPosition(0, -curSpeed * Time::GetDeltaTime());
	if (isD) tr->AddPosition(curSpeed * Time::GetDeltaTime(), 0);
}