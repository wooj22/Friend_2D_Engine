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
	}
	~Cat() override {}

	/* GameObject Cycle */
	void Awake() override {}			 // 오브젝트가 생성될 때
	void SceneStartInit() override {}	 // Scene의 Start
	void Update() override {}			 // Scene의 Update
	void Destroyed() override {}		 // Scene의 Exit, GameObject Delete
};

