#pragma once
#include "../Friend_2D_EngineLib/GameObject.h"
#include "../Friend_2D_EngineLib/Transform.h"
#include "../Friend_2D_EngineLib/SpriteRenderer.h"
#include "../Friend_2D_EngineLib/Animator.h"
#include "BCAnimatorController.h"

// Boss�� Hon�� �ε������� ������ effect
// �����ϱ� ������ Script Component ���� �ȸ���

class BossHitEffect : public GameObject
{
public:
	Transform* transform;
	SpriteRenderer* spriteRenderer;
	Animator* animator;
	BCAnimatorController* animatorController;

	BossHitEffect()
	{
		transform = AddComponent<Transform>();
		spriteRenderer = AddComponent<SpriteRenderer>();
		animator = AddComponent<Animator>();

		animatorController = new BCAnimatorController();
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

