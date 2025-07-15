#pragma once
#include "Component.h"
#include "Vector2.h"

enum class ColliderType
{
	Box, Circle
};

template<typename T>
T clamp(T value, T minVal, T maxVal)		// 범위 제한
{
    if (value < minVal) return minVal;
    else if (value > maxVal) return maxVal;
    else return value;
}

class ICollider : public Component
{
public:
	// default type
	ColliderType colliderType = ColliderType::Box;

	// collision, trigger
	bool isTrigger = false;             

	// bound
	float minX, maxX, minY, maxY;

	// collision data
	std::unordered_set<ICollider*> currentFrameCollisions;
	std::unordered_set<ICollider*> lastFrameCollisions;

	// cycle
	virtual ~ICollider() = default;
	virtual void UpdateBounds() = 0;
	virtual bool isCollision(ICollider* other) = 0;
	virtual void FinalizeCollision() = 0;

	// collision event
	virtual void OnCollisionEnter(ICollider* other) = 0;
	virtual void OnCollisionStay(ICollider* other) = 0;
	virtual void OnCollisionExit(ICollider* other) = 0;
	virtual void OnTriggerEnter(ICollider* other) = 0;
	virtual void OnTriggerStay(ICollider* other) = 0;
	virtual void OnTriggerExit(ICollider* other) = 0;

	// debug draw
	virtual void DebugColliderDraw() {}
};
