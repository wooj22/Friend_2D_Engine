#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h";
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/TextRenderer.h"

class Fish : public GameObject
{
public:
	Transform* transform;
	SpriteRenderer* sr;

	void Start() override;
	void Update() override;
	void Destroy() override;
};

