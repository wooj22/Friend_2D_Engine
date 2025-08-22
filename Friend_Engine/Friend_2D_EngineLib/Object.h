#pragma once
#include "ObjectTable.h"

/* [Object]
* Scene, GameObject, Component�� �⺻ Ŭ������
* ������ �� ObjectTable�� ������ �޸� �ּҸ� ����ϰ�, �޸𸮿��� �Ҹ�� �� �����Ͽ�
* �ν��Ͻ��� ���� �޸𸮿� ����ִ��� Ȯ���� �� �ֵ��� �Ѵ�.
* GameObject ����, Component ����, �ݹ��Լ� ȣ�� ��� ��۸� ������ ������ �����Ѵ�.
* ObjectTable::Get().IsValid(object)
*/

class Object
{
public:
	// ��ȿ�� �˻�
	Object() { ObjectTable::Get().Register(this); }
	virtual ~Object() { ObjectTable::Get().Unregister(this); }
};

