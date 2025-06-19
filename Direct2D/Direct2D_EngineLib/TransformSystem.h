#pragma once
#include <vector>
#include "Singleton.h"
using namespace std;

class Transform;
class TransformSystem : public Singleton<TransformSystem>
{
private :
	vector<Transform*> components;

public:
	// componenet
	void Regist(Transform* component);
	void Unregist(Transform* component);

	// component system
	void Update();
};

