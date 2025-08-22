#pragma once
#include <vector>
#include <queue>
#include <cstdint>
#include <unordered_set>
#include "Singleton.h"

/* [Object Table]
* ��۸� �����͸� �����ϱ� ���� ������ Object(GameObject, Component, Scene)�� �������θ� �����ϴ� Ŭ����
* ��� Object�� �����ÿ� ObjectTable�� ��ϵǰ�, �Ҹ�ÿ� ObjectTable���� ���ŵȴ�.
*  ObjectTable::Get().IsValid(object) �Լ��� ���� �޸𸮿� ����ִ� �ν��Ͻ����� Ȯ���� �� ����Ѵ�.
*/

class Object;
class ObjectTable : public Singleton<ObjectTable>
{
private:
	std::unordered_set<Object*> map_objects;

public:
	bool IsValid(Object* instance) 
	{
		return map_objects.find(instance) != map_objects.end();
	}

	void Register(Object* instance) 
	{
		map_objects.insert(instance);
	}

	void Unregister(Object* instance) 
	{
		map_objects.erase(instance);
	}
};

