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

	// debug
	float debugTime = 1.0f;
	float bugger;

public:
	// game object cycle
	Cat() : GameObject("Cat\n")
	{
		// component
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
		rigidbody->gravityScale = 40;
	}

	void Update() override
	{
		collider->DebugColliderDraw();

		//DebugWOo();
	}

	void DebugWOo()
	{
		// debug
		bugger += Time::GetDeltaTime();
		if (bugger >= debugTime)
		{
			// bound
			wchar_t buffer[256];
			swprintf_s(buffer, L"UpdateBounds: minX=%.3f, maxX=%.3f, minY=%.3f, maxY=%.3f\n",
				collider->minX, collider->maxX, collider->minY, collider->maxY);
			OutputDebugStringW(buffer);

			// local transform position
			Vector2 localPos = transform->GetPosition();
			wchar_t posBuffer[128];
			swprintf_s(posBuffer, L"Transform Local Position: x=%.3f, y=%.3f\n", localPos.x, localPos.y);
			OutputDebugStringW(posBuffer);

			// world transform position
			Vector2 worldPos = transform->GetWorldPosition();
			wchar_t posBuffer2[128];
			swprintf_s(posBuffer2, L"Transform World Position: x=%.3f, y=%.3f\n", worldPos.x, worldPos.y);
			OutputDebugStringW(posBuffer2);

			bugger = 0;
		}
	}
};

