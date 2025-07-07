#include "CatController.h"
#include "../Direct2D_EngineLib/Transform.h"
#include "../Direct2D_EngineLib/AnimatorController.h"
#include "../Direct2D_EngineLib/Animator.h"
#include "../Direct2D_EngineLib/Input.h"
#include "../Direct2D_EngineLib/Time.h"

void CatController::OnEnable()
{
	tr = owner->GetComponent<Transform>();
	ac = owner->GetComponent<Animator>()->controller;
	tr->SetScale(3, 3);
}

void CatController::Update()
{
	InputCheak();

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

	ac->SetFloat("Speed", curSpeed);

	// animation change
	/*if (Input::GetKeyDown('1')) ac->PlayAnimation("Cat_Idle");
	if (Input::GetKeyDown('2')) ac->PlayAnimation("Cat_Walk");
	if (Input::GetKeyDown('3')) ac->PlayAnimation("Cat_Run");*/
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