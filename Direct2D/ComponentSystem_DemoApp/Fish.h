#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h";
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/Time.h"

// script component system Àû¿ë Àü
class Fish : public GameObject
{
private:
	float rotationSpeed = 120.0f;
	float rotationDirection = -1.0f;

public:
	Transform* transform;
	SpriteRenderer* sr;

	Fish() : GameObject("Fish") 
	{ 
		transform = AddComponent<Transform>();
		sr = AddComponent<SpriteRenderer>(); 
		OutputDebugStringA("Fish()\n"); 
	}
	~Fish() override { OutputDebugStringA("~Fish()\n"); }

	void Awake() override;
	void SceneStart() override;
	void Update() override;
	void Destroyed() override;

public:
	void Button1Click();
	void Button2Click();
};

