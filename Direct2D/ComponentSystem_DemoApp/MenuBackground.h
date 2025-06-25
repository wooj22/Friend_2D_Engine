#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h";
#include "../Direct2D_EngineLib/SpriteRenderer.h"

// script component system Àû¿ë Àü
class MenuBackground : public GameObject
{
public:
	Transform* transform;
	SpriteRenderer* spriteRenderer;

	void Awake() override;
	void Start() override;
	void Update() override;
	void Destroyed() override;
};

