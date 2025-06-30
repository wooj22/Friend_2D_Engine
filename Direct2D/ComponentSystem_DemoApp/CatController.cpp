#include "CatController.h"

void CatController::OnEnable()
{
	// get component
	transform = this->owner->GetComponent<Transform>();
	sr = this->owner->GetComponent<SpriteRenderer>();
	tr = this->owner->GetComponent<WorldTextRenderer>();

	// set
	transform->SetPosition(0, 0);
	sr->SetImage(L"../Resource/Cat.png");
	tr->SetText(L"나 잡아봐라\n [Spacebar] 씬 변경");
	tr->SetColor(D2D1::ColorF(D2D1::ColorF::Yellow));
	tr->SetLayout(300, 100);
}

void CatController::Update()
{
	transform->AddPosition(0, moveSpeed * moveDirection * Time::GetDeltaTime());
	
	// gameobject find
	// GameObject::Find("Fish")->GetComponent<Transform>();
	// OnEnable()시에 Fish나 fishTransform이 생성되어있지 않을 수도 있어
	// onwer의 Start()시점에서 Find로 저장함
	fishTransform->AddRotation(120 * -1 * Time::GetDeltaTime());
}

void CatController::OnDestroy() 
{
	
}

void CatController::Button1Click()
{
	moveDirection *= -1;
	tr->SetColor(D2D1::ColorF(D2D1::ColorF::Red));
}

void CatController::Button2Click()
{
	moveDirection *= -1;
	tr->SetColor(D2D1::ColorF(D2D1::ColorF::Yellow));
}