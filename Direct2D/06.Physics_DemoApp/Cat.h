#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h"
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/Animator.h"
#include "../Direct2D_EngineLib/Time.h"

#include "CatController.h"
#include "CatAnimatorController.h"
#include "CatText.h"

class Cat : public GameObject
{
private:
	// components
	Transform* transform;
	SpriteRenderer* spriteRenderer;
	CatController* controller;		// script compoennt
	Animator* animator;

	// animation asset
	CatAnimatorController* catAnimatorController;

public:
	// child gameObject
	CatText* catText;

public:
	// game object cycle
	Cat() : GameObject("Cat")
	{
		transform = AddComponent<Transform>();
		spriteRenderer = AddComponent<SpriteRenderer>();
		controller = AddComponent<CatController>();
		animator = AddComponent<Animator>();

		catAnimatorController = new CatAnimatorController();  // animator controller
		animator->SetController(catAnimatorController);
	}
	~Cat() override { delete catAnimatorController; }

	void SceneStart() override
	{
		catText->transform->SetParent(this->transform);
		controller->infoText = catText->text;
	}
};

