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

	void Awake() override {}			 // 오브젝트가 생성되고 모든 컴포넌트의 OnEnable()이 실행된 이후
	void SceneStartInit() override {}	 // Scene의 Start
	void Update() override {}			 // Scene의 Update
	void Destroyed() override {}		 // Scene의 Exit, GameObject Delete
};

