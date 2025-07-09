#pragma once
#include <vector>
#include "Singleton.h"
using namespace std;

class BoxCollider;
class ColliderSystem : public Singleton<ColliderSystem>
{
private:
	vector<BoxCollider*> components;

public:
	// componenet
	void Regist(BoxCollider* component);
	void Unregist(BoxCollider* component);

	// component system
	void Update();
};
