#include "Sun.h"

void Sun::Awake() 
{
	transform = AddComponent<Transform>();
	sr = AddComponent<SpriteRenderer>();
}

void Sun::SceneStartInit()
{
	transform->SetPosition(0, 0);
	transform->SetScale(2.5, 2.5);
	sr->CreateTexture2D("../Resource/Sun.png");
}

void Sun::Update()
{
	transform->AddRotation(-rotationSpeed * Time::GetDeltaTime());
}

void Sun::Destroyed()
{

}