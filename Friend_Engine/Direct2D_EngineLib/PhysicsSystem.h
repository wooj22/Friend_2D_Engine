#pragma once
#include <vector>
#include "Singleton.h"
using namespace std;

/* PhysicsSystem�� ����
* 1. Rigidbody ������Ʈ�� FixedUpdate() -> ���� ���� ���� -> transform udpate
*/

class Rigidbody;
class PhysicsSystem : public Singleton<PhysicsSystem>
{
private:
	vector<Rigidbody*> components;
	vector<Rigidbody*> pending_components;

public:
	// componenet
	void Regist(Rigidbody* component);
	void Unregist(Rigidbody* component);

	// component system
	void FixedUpdate();
};

