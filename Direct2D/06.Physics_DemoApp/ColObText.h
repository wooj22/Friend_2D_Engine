#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h"
#include "../Direct2D_EngineLib/WorldTextRenderer.h"

class ColObText : public GameObject
{
public:
	// components
	Transform* transform;
	WorldTextRenderer* text;

public:
	// game object cycle
	ColObText()
	{
		transform = AddComponent<Transform>();
		text = AddComponent<WorldTextRenderer>();

		text->SetLayout(150, 100);
		text->SetFontSize(13);
		text->SetColor(D2D1::ColorF(D2D1::ColorF::YellowGreen));
		text->SetText(L"im collider");
	}
	~ColObText() override {}
};

