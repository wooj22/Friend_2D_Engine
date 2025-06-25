#include "MenuBackground.h"

void MenuBackground::Awake()
{
	transform = AddComponent<Transform>();
	spriteRenderer = AddComponent<SpriteRenderer>();
}
	
void MenuBackground::Start()
{
	spriteRenderer->SetImage(L"../Resource/Ground.jpg");
	transform->SetScale(5, 5);
}

void MenuBackground::Update()
{
	
}

void MenuBackground::Destroyed()
{

}