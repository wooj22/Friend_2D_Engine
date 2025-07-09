#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h"
#include "../Direct2D_EngineLib/SpriteRenderer.h"

class Cloud : public GameObject
{
public:
	// components
	Transform* transform;
	SpriteRenderer* spriteRenderer;

public:
	Cloud() : GameObject("Cloud")
	{
		transform = AddComponent<Transform>();
		spriteRenderer = AddComponent<SpriteRenderer>();

		auto cloud = ResourceManager::Get().CreateTexture2D("../Resource/Cloud.png");
		spriteRenderer->sprite = ResourceManager::Get().CreateSprite(cloud, "Cloud");
	}
	~Cloud() override {}
};

