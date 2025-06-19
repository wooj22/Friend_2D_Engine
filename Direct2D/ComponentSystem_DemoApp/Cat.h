#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/TextRenderer.h"

class Cat : public GameObject
{
public:
	Transform* transform;
	SpriteRenderer* sr;
	TextRenderer* tr;
};

