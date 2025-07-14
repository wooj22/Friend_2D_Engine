#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h"
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/BoxCollider.h"

class Cloud : public GameObject
{
public:
	// components
	Transform* transform;
	SpriteRenderer* spriteRenderer;
	BoxCollider* collider;

public:
	Cloud() : GameObject("Cloud")
	{
		transform = AddComponent<Transform>();
		spriteRenderer = AddComponent<SpriteRenderer>();
		collider = AddComponent<BoxCollider>();

		auto cloud = ResourceManager::Get().CreateTexture2D("../Resource/Cloud.png");
		spriteRenderer->sprite = ResourceManager::Get().CreateSprite(cloud, "Cloud");
	}
	~Cloud() override {}

	void Awake() override
	{
		collider->size = { spriteRenderer->sprite->size.width,spriteRenderer->sprite->size.height };
	}
};

