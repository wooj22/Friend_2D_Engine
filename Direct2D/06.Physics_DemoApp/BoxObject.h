#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h"
#include "../Direct2D_EngineLib/BoxCollider.h"
#include "../Direct2D_EngineLib/CircleCollider.h"
#include "../Direct2D_EngineLib/Rigidbody.h"
#include "../Direct2D_EngineLib/Time.h"
#include "../Direct2D_EngineLib/Input.h"
#include "CollisionEventCheak.h"

class BoxObject : public GameObject
{
private:
	float moveSpeed = 100.0f;

public:
	Transform* transform;
	Rigidbody* rigidbody;
	BoxCollider* collider;
	CollisionEventCheak* testScript;		// -> collision event

	BoxObject()
	{
		transform = AddComponent<Transform>();
		rigidbody = AddComponent<Rigidbody>();
		collider = AddComponent<BoxCollider>();
		testScript = AddComponent<CollisionEventCheak>();
	}

	~BoxObject() {}

	void Awake() override
	{
		transform->SetPosition(0, 100);
		collider->isTrigger = false;
		collider->size = { 50,50 };
		//collider->radius = 30;
		//collider->offset = { 10,10};
		rigidbody->useGravity = false;
	}

	void Update() override
	{
		// move
		Vector2 inputDir = Vector2::zero;

		if (Input::GetKey('W'))    inputDir.y += 1;
		if (Input::GetKey('A'))  inputDir.x -= 1;
		if (Input::GetKey('S'))  inputDir.y -= 1;
		if (Input::GetKey('D')) inputDir.x += 1;

		inputDir = inputDir.Normalized();
		rigidbody->velocity = inputDir * moveSpeed;

		// collider draw
		collider->DebugColliderDraw();

		// spacebar -> trigger
		if (Input::GetKeyDown(VK_SPACE)) collider->isTrigger = !collider->isTrigger;
	}
};

