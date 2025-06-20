#include "Sun.h"

void Sun::Awake() 
{
	transform = AddComponent<Transform>();
	sr = AddComponent<SpriteRenderer>();
}

void Sun::Start()
{
	transform->SetPosition(0, 0);
	transform->SetScale(2.5, 2.5);
	sr->SetImage(L"../Resource/Sun.png");
}

void Sun::Update()
{
	transform->AddRotation(-0.3);
}

void Sun::Destroy()
{

}