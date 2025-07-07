#pragma once
#include "../Direct2D_EngineLib/Script.h"
#include "../Direct2D_EngineLib/Transform.h";
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/WorldTextRenderer.h"
#include "../Direct2D_EngineLib/Time.h"

class CatController : public Script
{
private: 
	Transform* transform;
	SpriteRenderer* sr;
	WorldTextRenderer* tr;

	float walkSpeed = 100.0f;
	float moveDirection = -1.0f;

public:
	// find other gameobject component
	Transform* fishTransform;

public:
	// component cycle
	CatController() { OutputDebugStringA("CatController()\n"); }
	~CatController() override { OutputDebugStringA("~CatController()\n"); }

	void OnEnable() override;
	void Update() override;
	void OnDestroy() override;


public:
	// function
	void Button1Click();
	void Button2Click();
};

