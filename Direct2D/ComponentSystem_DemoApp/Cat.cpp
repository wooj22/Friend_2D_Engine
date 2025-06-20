#include "Cat.h"

void Cat::Start() 
{
	transform = AddComponent<Transform>();
	sr = AddComponent<SpriteRenderer>();
	tr = AddComponent<TextRenderer>();

	transform->SetPosition(0, 0);
	sr->SetImage(L"../Resource/Cat.png");
	tr->SetText(L"³ª Àâ¾ÆºÁ¶ó");
	tr->SetColor(D2D1::ColorF(D2D1::ColorF::Yellow));
	tr->SetLayout(300, 100);
}

void Cat::Update() 
{
	transform->AddPosition(0, -1);
}

void Cat::Destroy() 
{
	
}