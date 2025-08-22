#pragma once
#include "../Friend_2D_EngineLib/GameObject.h"
#include "../Friend_2D_EngineLib/Transform.h"
#include "../Friend_2D_EngineLib/SpriteRenderer.h"
#include "../Friend_2D_EngineLib/Animator.h"
#include "HCAnimatorController.h"

// Hon�� Hon�� �ε������� ������ effect
// �����ϱ� ������ Script Component ���� �ȸ���

class HonCollisionEffect : public GameObject
{
public:
	Transform* transform;
	SpriteRenderer* spriteRenderer;
	Animator* animator;
	HCAnimatorController* animatorController;

	HonCollisionEffect()
	{
		transform = AddComponent<Transform>();
		spriteRenderer = AddComponent<SpriteRenderer>();
		animator = AddComponent<Animator>();

		animatorController = new HCAnimatorController();
		animator->SetController(animatorController);
		spriteRenderer->layer = 12;
	}

	void Update() override
	{
		// animation ��� �ѹ� ������ destory
		if (animatorController->currentTime >= animatorController->curState->clip->duration)
		{
			Destroy();
		}
	}
};
