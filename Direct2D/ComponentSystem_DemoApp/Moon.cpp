#include "Moon.h"

void Moon::Awake()
{
	
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