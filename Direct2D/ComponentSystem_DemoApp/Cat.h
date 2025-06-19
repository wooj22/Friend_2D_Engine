#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/SpriteRenderer.h"

class Cat : public GameObject
{
public:
	Transform* transform;
	SpriteRenderer* sr;
};

