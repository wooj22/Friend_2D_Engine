#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h";
#include "../Direct2D_EngineLib/SpriteRenderer.h"

class Earth : public GameObject
{
public:
	Transform* transform;
	SpriteRenderer* sr;

	void Awake() override;
	void Start() override;
	void Update() override;
	void Destroy() override;
};

