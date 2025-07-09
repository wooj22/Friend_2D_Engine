#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h";
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/Time.h"

// script component system Àû¿ë Àü
class Earth : public GameObject
{
private:
	float rotationSpeed = 70.0f;
public:
	Earth() {
		transform = AddComponent<Transform>();
		sr = AddComponent<SpriteRenderer>();
	}
	~Earth() override {}

	Transform* transform;
	SpriteRenderer* sr;

	void Awake() override;
	void SceneStart() override;
	void Update() override;
	void Destroyed() override;
};

