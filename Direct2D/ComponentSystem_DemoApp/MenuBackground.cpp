#include "MenuBackground.h"

void MenuBackground::Awake()
{
	
}
	
void MenuBackground::SceneStart()
{
	spriteRenderer->CreateTexture2D("../Resource/Ground.jpg");
	transform->SetScale(5, 5);
}

void MenuBackground::Update()
{
	
}

void MenuBackground::Destroyed()
{

}