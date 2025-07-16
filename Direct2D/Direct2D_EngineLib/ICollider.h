#pragma once
#include <unordered_map>
#include "Component.h"
#include "Vector2.h"

/* 범위 제한 func */
template<typename T>
T clamp(T value, T minVal, T maxVal)		
{
    if (value < minVal) return minVal;
    else if (value > maxVal) return maxVal;
    else return value;
}

/* collider type */
enum class ColliderType
{
	Box, Circle
};

/* 충돌 관련 최소 데이터 */
struct ContactInfo
{
	Vector2 point;   // 충돌 지점
	Vector2 normal;  // 충돌 법선벡터(방향)
};

/* collider interface */
class ICollider : public Component
{
public:
	// default type
	ColliderType colliderType = ColliderType::Box;

	// collision, trigger
	bool isTrigger = false;             

	// bound
	float minX, maxX, minY, maxY;

	// collision data <충돌한 상대 콜라이더, 충돌정보>
	std::unordered_map<ICollider*, ContactInfo> currentFrameCollisions;
	std::unordered_map<ICollider*, ContactInfo> lastFrameCollisions;

	// cycle
	virtual ~ICollider() = default;
	virtual void UpdateBounds() = 0;
	virtual bool isCollision(ICollider* other, ContactInfo& outContact) = 0;
	virtual void FinalizeCollision() = 0;

	// collision event
	virtual void OnCollisionEnter(ICollider* other, ContactInfo& outContact) = 0;
	virtual void OnCollisionStay(ICollider* other, ContactInfo& outContact) = 0;
	virtual void OnCollisionExit(ICollider* other) = 0;
	virtual void OnTriggerEnter(ICollider* other) = 0;
	virtual void OnTriggerStay(ICollider* other) = 0;
	virtual void OnTriggerExit(ICollider* other) = 0;

	// debug draw
	virtual void DebugColliderDraw() {}
};
