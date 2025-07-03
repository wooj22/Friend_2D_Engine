#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h";
#include "../Direct2D_EngineLib/SpriteRenderer.h"

// script component system Àû¿ë Àü
class MenuBackground : public GameObject
{
public:
	Transform* transform;
	SpriteRenderer* spriteRenderer;

	MenuBackground() { OutputDebugStringA("MenuBackground()\n"); }
	~MenuBackground() override { OutputDebugStringA("~MenuBackground()\n"); }

	void Awake() override;
	void SceneStartInit() override;
	void Update() override;
	void Destroyed() override;
};

