#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h"
#include "../Direct2D_EngineLib/CircleCollider.h"
#include "../Direct2D_EngineLib/Rigidbody.h"
#include "../Direct2D_EngineLib/Time.h"
#include "../Direct2D_EngineLib/Input.h"
#include "CollisionEventCheak.h"

class CircleObject : public GameObject
{
private:
	float moveSpeed = 5.0f;

public:
	Transform* transform;
	Rigidbody* rigidbody;
	CircleCollider* collider;
	CollisionEventCheak* testScript;		// -> collision event

	CircleObject()
	{
		transform = AddComponent<Transform>();
		rigidbody = AddComponent<Rigidbody>();
		collider = AddComponent<CircleCollider>();
		testScript = AddComponent<CollisionEventCheak>();
	}

	~CircleObject() {}

	void Awake() override
	{
		transform->SetPosition(0, -100);
		collider->isTrigger = false;
		collider->radius = 30;
		rigidbody->useGravity = false;
	}

	void Update() override
	{
		// move
		Vector2 inputDir = Vector2::zero;

		if (Input::GetKey(VK_UP))    inputDir.y += 1;
		if (Input::GetKey(VK_DOWN))  inputDir.y -= 1;
		if (Input::GetKey(VK_LEFT))  inputDir.x -= 1;
		if (Input::GetKey(VK_RIGHT)) inputDir.x += 1;

		inputDir = inputDir.Normalized();
		rigidbody->velocity = inputDir * moveSpeed;

		// spacebar -> trigger
		if (Input::GetKeyDown(VK_SPACE)) collider->isTrigger = !collider->isTrigger;
	}
};

