#pragma once
#include <vector>
#include "Singleton.h"
#include "RaycastHit.h"
using namespace std;

class ICollider;
class ColliderSystem : public Singleton<ColliderSystem>
{
private:
	vector<ICollider*> components;

public:
	// componenet
	void Regist(ICollider* component);
	void Unregist(ICollider* component);

	// component system
	void FixedUpdate();

public:
	// func
	// ray hit collision
	RaycastHit Raycast(const Ray& ray, float maxDistance);
};
