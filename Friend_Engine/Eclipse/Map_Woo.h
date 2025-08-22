#pragma once
#include "../Friend_2D_EngineLib/GameObject.h"
#include "../Friend_2D_EngineLib/Transform.h"
#include "../Friend_2D_EngineLib/BoxCollider.h"
#include "../Friend_2D_EngineLib/Rigidbody.h"

class Map_Woo : public GameObject
{
public:
	// components
	Transform* transform;
	BoxCollider* collider;

	Map_Woo() : GameObject("Ground")
	{
		transform = AddComponent<Transform>();
		collider = AddComponent<BoxCollider>();
		collider->size = { 2560, 50 };

		collider->isFlatform = true;
	}

	void Update() override
	{
		collider->DebugColliderDraw();
	}
};

