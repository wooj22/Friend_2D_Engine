#pragma once
#include <vector>
#include "Singleton.h"
#include "ITransform.h"
using namespace std;

/* TransformSystem�� ����
* 1. tranform, rectTrasfrom�� �ڽ��� matrix(local, world, screen)�� update�ϰ� �Ѵ�.
*/


class Transform;
class RectTransform;
class TransformSystem : public Singleton<TransformSystem>
{
private :
	vector<ITransform*> components;
	vector<ITransform*> pending_components;

public:
	// componenet
	void Regist(ITransform* component);
	void Unregist(ITransform* component);

	// component system
	void Update();
};

