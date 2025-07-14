#pragma once
#include "Component.h"
#include "Vector2.h"

enum class ColliderType
{
	Box, Circle
};

class ICollider : public Component
{
public:
	// default type
	ColliderType colliderType = ColliderType::Box;
	bool isTrigger = false;             // collision, trigger

	// cycle
	virtual ~ICollider() = default;
	virtual bool isCollision(ICollider* other) = 0;

	// collision event
	virtual void OnCollisionEnter(ICollider* other) = 0;
	virtual void OnTriggerEnter(ICollider* other) = 0;

	// debug draw
	virtual void DebugColliderDraw() {}
};
