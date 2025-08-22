#pragma once
#include "../Friend_2D_EngineLib/GameObject.h"
#include "../Friend_2D_EngineLib/Transform.h"
#include "../Friend_2D_EngineLib/SpriteRenderer.h"
#include "../Friend_2D_EngineLib/Animator.h"

#include "LandingAnimatorController.h"

class PlayerLandingEffect : public GameObject
{
public:
	Transform* transform = nullptr;
	SpriteRenderer* spriteRenderer = nullptr;

	Animator* landingAnimator = nullptr;
	LandingAnimatorController* animController = nullptr;

	PlayerLandingEffect() : GameObject("PlayerLandingEffect", "PlayerLandingEffect")
	{
		transform = AddComponent<Transform>();
		spriteRenderer = AddComponent<SpriteRenderer>();

		landingAnimator = AddComponent<Animator>();
		animController = new LandingAnimatorController();
		landingAnimator->SetController(animController);

		spriteRenderer->layer = 24; // 21;

	}
	~PlayerLandingEffect() override
	{
		delete animController;
	}

	void Awake() override
	{
		transform->SetPosition(0.0f, 0.0f);
		transform->SetScale(0.4f, 0.4f);
	}
};