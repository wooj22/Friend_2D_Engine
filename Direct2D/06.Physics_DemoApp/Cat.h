#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h"
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/Animator.h"
#include "../Direct2D_EngineLib/Time.h"
#include "../Direct2D_EngineLib/BoxCollider.h"
#include "../Direct2D_EngineLib/CircleCollider.h"

#include "CatController.h"
#include "CatAnimatorController.h"

// window : (1400, 800)

class Cat : public GameObject
{
public:
	// components
	Transform* transform;
	SpriteRenderer* spriteRenderer;
	BoxCollider* collider;
	CatController* controller;		// script compoennt
	Animator* animator;

	// animation asset
	CatAnimatorController* catAnimatorController;

public:
	// game object cycle
	Cat() : GameObject("Cat\n")
	{
		// component
		OutputDebugStringA("Cat Cat()\n");
		transform = AddComponent<Transform>();
		spriteRenderer = AddComponent<SpriteRenderer>();
		collider = AddComponent<BoxCollider>();
		controller = AddComponent<CatController>();
		animator = AddComponent<Animator>();

		// animator controller
		catAnimatorController = new CatAnimatorController();  
		animator->SetController(catAnimatorController);

		// setting
		transform->SetPosition(0, 100);
		collider->size = { 15, 10 };
		collider->isTrigger = false;
	}
	~Cat() override { delete catAnimatorController; };
};

