#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h"
#include "../Direct2D_EngineLib/WorldTextRenderer.h"

class CatText : public GameObject
{
public:
	// components
	Transform* transform;
	WorldTextRenderer* text;

public:
	// game object cycle
	CatText() : GameObject("CatText")
	{
		transform = AddComponent<Transform>();
		text = AddComponent<WorldTextRenderer>();

		transform->Translate(0, -15);
		text->SetLayout(70, 20);
		text->SetFontSize(4.5);
		text->SetColor(D2D1::ColorF(D2D1::ColorF::DarkBlue));
		text->SetText(L"World Text");

		text->layer = 10;
	}
	~CatText() override { }
};

