#pragma once
#include "../Friend_2D_EngineLib/GameObject.h"
#include "../Friend_2D_EngineLib/Transform.h"
#include "../Friend_2D_EngineLib/SpriteRenderer.h"
#include "../Friend_2D_EngineLib/Animator.h"
#include "../Friend_2D_EngineLib/Time.h"
#include "../Friend_2D_EngineLib/CircleCollider.h"
#include "../Friend_2D_EngineLib/Rigidbody.h"

#include "PlayerAreaController.h";
#include "AttackAnimatorController.h"

class PlayerAttackArea : public GameObject
{
	// [ components ]
	Transform* transform;
	SpriteRenderer* spriteRenderer;
	CircleCollider* collider;

	PlayerAreaController* controller;

	// [ animation ]
	Animator* animator;  
	AttackAnimatorController* animController;


public:
	PlayerAttackArea() : GameObject("PlayerAttackArea", "PlayerAttackArea")
	{
		transform = AddComponent<Transform>();
		spriteRenderer = AddComponent<SpriteRenderer>();
		collider = AddComponent<CircleCollider>();
		controller = AddComponent<PlayerAreaController>();

		// Animator & Controller �߰�
		animator = AddComponent<Animator>();
		animController = new AttackAnimatorController();
		animator->SetController(animController);

		spriteRenderer->layer = 2;
	}
	~PlayerAttackArea() override
	{
		delete animController;
	}

	void Awake() override
	{
		transform->SetPosition(0.0f, 0.0f);
		// transform->SetPosition(0.0f, 0.0f);
		transform->SetRotation(0.0f);
		transform->SetScale(0.7f, 0.7f); 

		collider->offset = { 0.0f, 0.0f };
		collider->radius = 130.0f; 
		collider->isTrigger = true;

		spriteRenderer->renderMode = RenderMode::Lit_ColorTint;

		// �ʱ� ��Ȱ��ȭ
		spriteRenderer->SetEnabled(false);
		collider->SetEnabled(false);
	}

	void Update() override
	{
		// AABB ���� 
		// if(collider->IsEnabled()) collider->DebugColliderDraw();
		// collider->DebugColliderDraw();
	}

	// ���� ���� Ȱ��ȭ + �ִϸ��̼� ����
	void Activate()
	{
		spriteRenderer->SetEnabled(true);
		collider->SetEnabled(true);
	}

	void Deactivate()
	{
		spriteRenderer->SetEnabled(false);
		collider->SetEnabled(false);
	}
};