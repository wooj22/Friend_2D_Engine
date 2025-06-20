#include "Fish.h"

void Fish::Start() 
{
	transform = AddComponent<Transform>();
	sr = AddComponent<SpriteRenderer>();

	transform->SetScale(0.3, 0.3);
	transform->SetRotation(-60);
	transform->SetPosition(300, 300);
	sr->SetImage(L"../Resource/Fish.png");
}

void Fish::Update() 
{
	transform->AddRotation(1);
}

void Fish::Destroy() 
{

}