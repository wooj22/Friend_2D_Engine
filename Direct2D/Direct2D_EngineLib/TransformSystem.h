#pragma once
#include <vector>
#include "Singleton.h"
#include "ITransform.h"
using namespace std;

class Transform;
class RectTransform;

class TransformSystem : public Singleton<TransformSystem>
{
private :
	vector<ITransform*> components;

public:
	// componenet
	void Regist(ITransform* component);
	void Unregist(ITransform* component);

	// component system
	void Update();
};

