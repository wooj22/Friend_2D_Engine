#pragma once
#include <Windows.h>
#include "Object.h"

/* [Component]
* 게임 오브젝트에 부착될 컴포넌트들의 Base Class
*/

class GameObject;
class Component : public Object
{
public:
    GameObject* gameObject = nullptr;

public:
    virtual ~Component() = default;

    /* Component Cycle */
    virtual void OnEnable() = 0;    // 컴포넌트 활성화시
    virtual void OnDestroy() = 0;   // 컴포넌트 or 게임오브젝트 파괴시
};

