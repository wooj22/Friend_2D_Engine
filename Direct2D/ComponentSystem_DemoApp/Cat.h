#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h";
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/WorldTextRenderer.h"
#include "CatController.h"

class Cat : public GameObject
{
public:
	Transform* transform;
	SpriteRenderer* sr;
	WorldTextRenderer* tr;
	CatController* catController;	// script component

	Cat() : GameObject("Cat") 
	{ 
		transform = AddComponent<Transform>();
		sr = AddComponent<SpriteRenderer>();
		tr = AddComponent<WorldTextRenderer>();
		catController = AddComponent<CatController>();
		OutputDebugStringA("Cat()\n"); 
	}
	~Cat() override { OutputDebugStringA("~Cat()\n"); }

	// scene->gameobject cycle
	void Awake() override;
	void SceneStartInit() override;
	void Update() override;
	void Destroyed() override;
};

