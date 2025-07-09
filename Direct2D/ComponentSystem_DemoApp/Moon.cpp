#include "Moon.h"

void Moon::Awake()
{
	
}

void Moon::SceneStart()
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