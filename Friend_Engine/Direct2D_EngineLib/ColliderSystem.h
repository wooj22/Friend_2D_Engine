#pragma once
#include <vector>
#include "Singleton.h"
#include "RaycastHit.h"
using namespace std;

/* ColliderSystem�� ����
* 1. Collider���� bound update
* 2. collision cheak(sap) -> �̺�Ʈ �Լ� ȣ�� ����
* 3. RayCast �߻��� ��� �ݶ��̴����� hit ���� ��� ��ȯ
*/

class ICollider;
class ColliderSystem : public Singleton<ColliderSystem>
{
private:
	vector<ICollider*> components;
	vector<ICollider*> pending_components;

public:
	// componenet
	void Regist(ICollider* component);
	void Unregist(ICollider* component);

	// component system
	void FixedUpdate();

public:
	// to CCD
	vector<ICollider*> GetColliders() { return components; }

public:
	// func
	// ray hit collision
	RaycastHit Raycast(const Ray& ray, float maxDistance);
};
