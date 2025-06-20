#include "Moon.h"

void Moon::Awake()
{
	transform = AddComponent<Transform>();
	sr = AddComponent<SpriteRenderer>();
}

void Moon::Start()
{
	transform->SetPosition(50, 0);
	sr->SetImage(L"../Resource/Moon.png");
}

void Moon::Update()
{
	transform->AddRotation(-0.7);
}

void Moon::Destroy()
{

}