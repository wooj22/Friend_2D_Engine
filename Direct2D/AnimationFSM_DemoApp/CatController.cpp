#include "CatController.h"
#include "../Direct2D_EngineLib/Transform.h"
#include "../Direct2D_EngineLib/AnimatorController.h"
#include "../Direct2D_EngineLib/Animator.h"
#include "../Direct2D_EngineLib/Input.h"

void CatController::OnEnable()
{
	tr = owner->GetComponent<Transform>();
	ac = owner->GetComponent<Animator>()->controller;
	tr->SetScale(3, 3);
}

void CatController::Update()
{
	// animation change
	if (Input::GetKeyDown('1')) ac->PlayAnimation("Cat_Idle");
	if (Input::GetKeyDown('2')) ac->PlayAnimation("Cat_Walk");
	if (Input::GetKeyDown('3')) ac->PlayAnimation("Cat_Run");
}

void CatController::OnDestroy()
{

}