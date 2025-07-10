#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h";
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "CatController.h"
#include "../Direct2D_EngineLib/Time.h"

class Cat : public GameObject
{
public:
	Transform* transform;
	SpriteRenderer* spriteRenderer;
	CatController* controller;

	Cat() : GameObject("Cat")
	{
		transform = AddComponent<Transform>();
		spriteRenderer = AddComponent<SpriteRenderer>();
		controller = AddComponent<CatController>();

		// resource create
		auto catTexture = ResourceManager::Get().CreateTexture2D("../Resource/Cat.png");
		auto new_sprite = ResourceManager::Get().CreateSprite(catTexture, "Cat_Sprite");
		spriteRenderer->sprite = new_sprite;
	}
	~Cat() override {}
};

