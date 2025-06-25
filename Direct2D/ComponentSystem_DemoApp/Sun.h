#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h";
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/Time.h"

// script component system Àû¿ë Àü
class Sun : public GameObject
{
private:
	float rotationSpeed = 50.0f;
public:
	Transform* transform;
	SpriteRenderer* sr;

	void Awake() override;
	void Start() override;
	void Update() override;
	void Destroyed() override;
};

