#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h"
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "CatController.h"
#include "../Direct2D_EngineLib/Time.h"

// test
#include "CatIdleClip.h"

class Cat : public GameObject
{
public:
	Transform* transform;
	SpriteRenderer* spriteRenderer;
	CatController* controller;

	// animation test
	CatIdleClip* idleClip = nullptr;
	float animationTime = 0.0f;
	int currentFrameIndex = 0;

	Cat() : GameObject("Cat")
	{
		transform = AddComponent<Transform>();
		spriteRenderer = AddComponent<SpriteRenderer>();
		controller = AddComponent<CatController>();
	}
	~Cat() override { delete idleClip; }

	/* GameObject Cycle */
	void Awake() override				 // 오브젝트가 생성되고 모든 컴포넌트의 OnEnable()이 실행된 이후
	{
		// resource create
		/*auto catTexture = ResourceManager::Get().CreateTexture2D("../Resource/Texture/Cat_Idle.png");
		auto new_sprite = ResourceManager::Get().CreateSprite(catTexture, "Cat_Idle");
		spriteRenderer->sprite = new_sprite;*/

		// animation test
		idleClip = new CatIdleClip();
		spriteRenderer->sprite = idleClip->frames[0].sprite;
		transform->SetScale(5, 5);
	}
	void SceneStartInit() override {}	 // Scene의 Start
	void Update() override				 // Scene의 Update
	{
		animationTime += Time::GetDeltaTime();

		if (animationTime >= idleClip->duration)
		{
			if (idleClip->loop)
				animationTime = 0.0f;
			else
				animationTime = idleClip->duration;
		}

		int frameIndex = 0;
		for (size_t i = 0; i < idleClip->frames.size(); ++i)
		{
			if (animationTime >= idleClip->frames[i].time)
				frameIndex = (int)i;
			else
				break;
		}

		if (frameIndex != currentFrameIndex)
		{
			currentFrameIndex = frameIndex;
			spriteRenderer->sprite = idleClip->frames[currentFrameIndex].sprite;
		}
	}
	void Destroyed() override {}		 // Scene의 Exit, GameObject Delete
};

