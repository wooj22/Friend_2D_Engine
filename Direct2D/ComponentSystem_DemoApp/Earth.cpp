#include "Earth.h"

void Earth::Awake()
{
	transform = AddComponent<Transform>();
	sr = AddComponent<SpriteRenderer>();
}

void Earth::Start()
{
	transform->SetPosition(150, 0);
	transform->SetScale(0.5, 0.5);
	sr->SetImage(L"../Resource/Earth.png");
}

void Earth::Update()
{
	transform->AddRotation(-0.5);
}

void Earth::Destroy()
{

}