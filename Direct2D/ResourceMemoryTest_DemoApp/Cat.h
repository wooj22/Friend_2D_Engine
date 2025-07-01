#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h";
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "CatController.h"
#include "../Direct2D_EngineLib/Time.h"

class Cat : public GameObject
{
public:
	Transform* transform;
	SpriteRenderer* spriteRenderer;
	CatController* controller;

	Cat() : GameObject("Cat")
	{
		transform = AddComponent<Transform>();
		spriteRenderer = AddComponent<SpriteRenderer>();
		controller = AddComponent<CatController>();
	}
	~Cat() override {}

	void Awake() override {}
	void Start() override {}
	void Update() override {}
	void Destroyed() override {}
};

