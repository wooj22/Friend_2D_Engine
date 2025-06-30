#include "Fish.h"

void Fish::Awake()
{
	transform = AddComponent<Transform>();
	sr = AddComponent<SpriteRenderer>();
}

void Fish::Start() 
{
	transform->SetScale(0.3, 0.3);
	transform->SetRotation(-60);
	transform->SetPosition(300, 300);
	sr->SetImage(L"../Resource/Fish.png");
}

void Fish::Update() 
{
	//transform->AddRotation(rotationSpeed * rotationDirection * Time::GetDeltaTime());
}

void Fish::Destroyed() 
{

}

void Fish::Button1Click() 
{
	rotationDirection *= -1;
	transform->AddPosition(50, 0);
}

void Fish::Button2Click()
{
	rotationDirection *= -1;
	transform->AddPosition(-50, 0);
}