#pragma once
#include <unordered_map>
#include "Component.h"
#include "Vector2.h"
#include "RaycastHit.h"

template<typename T>
T clamp(T value, T minVal, T maxVal)		
{
    if (value < minVal) return minVal;
    else if (value > maxVal) return maxVal;
    else return value;
}

/* ContactInfo : �ݶ��̴��� �ݶ��̴��� �浹 ���� */
struct ContactInfo
{
	Vector2 point;   // �浹 ����
	Vector2 normal;  // �浹 �������� : �з������� ����(��� �ݶ��̴��� �о�� ����)
	float depth;     // ħ�� ����
};

/* collider type : �ݶ��̴� ���� */
enum class ColliderType
{
	Box, Circle
};

/* collider interface*/
class ICollider : public Component
{
public:
	// default type
	ColliderType colliderType = ColliderType::Box;

	// collision, trigger
	bool isTrigger = false;             

	// bound
	float minX, maxX, minY, maxY;

	// collision data <�浹�� ��� �ݶ��̴�, �浹����>
	// Enter / Stay / Eixt
	std::unordered_map<ICollider*, ContactInfo> currentFrameCollisions;
	std::unordered_map<ICollider*, ContactInfo> lastFrameCollisions;

	// cycle
	virtual ~ICollider() = default;
	virtual void UpdateBounds() = 0;
	virtual bool isCollision(ICollider* other, ContactInfo& contact) = 0;
	virtual void FinalizeCollision() = 0;

	// collision cheak
	// Box, Circle�� ���� �ݶ��̴�����
	// ray cast hit
	virtual bool Raycast(const Ray& ray, float maxDistance, RaycastHit& hitInfo) = 0;

	// collision event
	virtual void OnCollisionEnter(ICollider* other, ContactInfo& contact) = 0;
	virtual void OnCollisionStay(ICollider* other, ContactInfo& contact) = 0;
	virtual void OnCollisionExit(ICollider* other, ContactInfo& contact) = 0;
	virtual void OnTriggerEnter(ICollider* other, ContactInfo& contact) = 0;
	virtual void OnTriggerStay(ICollider* other, ContactInfo& contact) = 0;
	virtual void OnTriggerExit(ICollider* other, ContactInfo& contact) = 0;

	// debug draw
	virtual void DebugColliderDraw() {}
};
