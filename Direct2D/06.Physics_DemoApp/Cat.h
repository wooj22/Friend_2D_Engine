#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h"
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/Animator.h"
#include "../Direct2D_EngineLib/Time.h"
#include "../Direct2D_EngineLib/BoxCollider.h"
#include "../Direct2D_EngineLib/CircleCollider.h"
#include "../Direct2D_EngineLib/Rigidbody.h"

#include "CatController.h"
#include "CatAnimatorController.h"

// window : (1400, 800)

class Cat : public GameObject
{
public:
	// components
	Transform* transform;
	SpriteRenderer* spriteRenderer;
	Rigidbody* rigidbody;
	BoxCollider* collider;
	Animator* animator;
	CatController* controller;		// script compoennt

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
		rigidbody = AddComponent<Rigidbody>();
		collider = AddComponent<BoxCollider>();
		animator = AddComponent<Animator>();
		controller = AddComponent<CatController>();
	}
	~Cat() override { delete catAnimatorController; };

	void Awake() override
	{
		// animator controller
		catAnimatorController = new CatAnimatorController();
		animator->SetController(catAnimatorController);

		// setting
		transform->SetPosition(0, 100);
		transform->SetScale(3, 3);
		collider->size = { 15, 10 };
		collider->isTrigger = false;
		rigidbody->useGravity = true;
		rigidbody->gravityScale = 30;
	}
};

