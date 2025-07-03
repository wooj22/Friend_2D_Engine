#pragma once
#include <Windows.h>
#include "Object.h"

class GameObject;
class Component : public Object
{
public:
    GameObject* owner = nullptr;

public:
    virtual ~Component() = default;

    /* Component Cycle */
    virtual void OnEnable() = 0;    // GameObject의 모든 Compoent가 생성된 뒤 초기화로 호출
    virtual void OnDestroy() = 0;   // GameObject가 파괴되거나, 컴포넌트가 파괴될 때 호출
};

