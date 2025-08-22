#pragma once
#include <Windows.h>
#include "Object.h"

/* [Component]
* ���� ������Ʈ�� ������ ������Ʈ���� Base Class
*/

class GameObject;
class Component : public Object
{
public:
    GameObject* gameObject = nullptr;

private:
    bool enabled = true;

public:
    virtual ~Component() = default;

    /* Component Cycle */
    virtual void OnEnable_Inner() = 0;    // ������Ʈ Ȱ��ȭ��
	virtual void OnDisable_Inner() = 0;   // ������Ʈ ��Ȱ��ȭ��
    virtual void OnDestroy_Inner() = 0;   // ������Ʈ or ���ӿ�����Ʈ �ı���


    /* Enabled Func */
	bool IsEnabled() const { return enabled; }
	void SetEnabled(bool new_enable)
	{
		if (enabled == new_enable) return;
		enabled = new_enable;

		if (enabled)
			OnEnable_Inner();
		else
			OnDisable_Inner();
	}
};

