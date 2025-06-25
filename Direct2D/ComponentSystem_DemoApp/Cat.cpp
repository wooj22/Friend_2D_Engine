#include "Cat.h"

void Cat::Awake()
{
	transform = AddComponent<Transform>();
	sr = AddComponent<SpriteRenderer>();
	tr = AddComponent<TextRenderer>();
}

void Cat::Start() 
{
	transform->SetPosition(0, 0);
	sr->SetImage(L"../Resource/Cat.png");
	tr->SetText(L"³ª Àâ¾ÆºÁ¶ó\n [Spacebar] ¾À º¯°æ");
	tr->SetColor(D2D1::ColorF(D2D1::ColorF::Yellow));
	tr->SetLayout(300, 100);
}

void Cat::Update()
{
	transform->AddPosition(0, moveSpeed * moveDirection * Time::GetDeltaTime());
}

void Cat::Destroy() 
{
	
}

void Cat::Button1Click() 
{
	moveDirection *= -1;
	tr->SetColor(D2D1::ColorF(D2D1::ColorF::Red));
}

void Cat::Button2Click()
{
	moveDirection *= -1;
	tr->SetColor(D2D1::ColorF(D2D1::ColorF::Yellow));
}