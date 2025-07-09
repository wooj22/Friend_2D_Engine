#pragma once
#include <vector>
#include "Singleton.h"
using namespace std;

class Rigidbody;
class PhysicsSystem : public Singleton<PhysicsSystem>
{
private:
	vector<Rigidbody*> components;

public:
	// componenet
	void Regist(Rigidbody* component);
	void Unregist(Rigidbody* component);

	// component system
	void Update();
};

