#pragma once
#include "../Friend_2D_EngineLib/GameObject.h"
#include "../Friend_2D_EngineLib/Transform.h"
#include "../Friend_2D_EngineLib/SpriteRenderer.h"
#include "../Friend_2D_EngineLib/CircleCollider.h"
#include "../Friend_2D_EngineLib/Rigidbody.h"
#include "BulletController.h"

class Bullet : public GameObject
{
public:
	// components
	Transform* transform;
	SpriteRenderer* spriteRenderer;
	Rigidbody* rigidbody;
	CircleCollider* collider;
	BulletController* controller;

	Bullet()
	{
		transform = AddComponent<Transform>();
		spriteRenderer = AddComponent<SpriteRenderer>();
		rigidbody = AddComponent<Rigidbody>();
		collider = AddComponent<CircleCollider>();
		controller = AddComponent<BulletController>();

		name = "Bullet";
		tag = "Bullet";

		transform->SetScale(0.4, 0.4);

		auto texture = ResourceManager::Get().CreateTexture2D("../Resource/Woo/Boss/BossBullet.png");
		auto new_sprite = ResourceManager::Get().CreateSprite(texture, "Bullet");
		spriteRenderer->sprite = new_sprite;
		spriteRenderer->layer = 10;

		rigidbody->isKinematic = true;
		collider->isTrigger = true;
		collider->radius = 27;

		spriteRenderer->renderMode = RenderMode::Lit_Glow;
	}
};

