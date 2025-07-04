#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h";
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "CatController.h"
#include "../Direct2D_EngineLib/Time.h"

// test
//#include "CatIdleClip.h"

class Cat : public GameObject
{
public:
	Transform* transform;
	SpriteRenderer* spriteRenderer;
	CatController* controller;
	//CatIdleClip idle;

	Cat() : GameObject("Cat")
	{
		transform = AddComponent<Transform>();
		spriteRenderer = AddComponent<SpriteRenderer>();
		controller = AddComponent<CatController>();
	}
	~Cat() override {}

	/* GameObject Cycle */
	void Awake() override				 // 오브젝트가 생성되고 모든 컴포넌트의 OnEnable()이 실행된 이후
	{
		// resource create
		auto catTexture = ResourceManager::Get().CreateTexture2D("../Resource/Texture/Cat_Idle.png");
		auto new_sprite = ResourceManager::Get().CreateSprite(catTexture, "Cat_Idle");
		spriteRenderer->sprite = new_sprite;
	}
	void SceneStartInit() override {}	 // Scene의 Start
	void Update() override {}			 // Scene의 Update
	void Destroyed() override {}		 // Scene의 Exit, GameObject Delete
};

