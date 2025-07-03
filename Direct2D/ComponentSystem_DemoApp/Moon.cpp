#include "Moon.h"

void Moon::Awake()
{
	transform = AddComponent<Transform>();
	sr = AddComponent<SpriteRenderer>();
}

void Moon::SceneStartInit()
{
	transform->SetPosition(50, 0);
	sr->CreateTexture2D("../Resource/Moon.png");
}

void Moon::Update()
{
	transform->AddRotation(-rotationSpeed * Time::GetDeltaTime());
}

void Moon::Destroyed()
{

}