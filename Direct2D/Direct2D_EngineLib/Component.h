#pragma once
#include <Windows.h>
#include "Object.h"

/* [Component]
* 게임 오브젝트에 부착될 컴포넌트들의 Base Class
* 게임 오브젝트가 생성되고 해당 오브젝트의 컴포넌트들이 모두 생성된 뒤, OnEnable()이 호출된다.
*/

class GameObject;
class Component : public Object
{
public:
    GameObject* owner = nullptr;

public:
    virtual ~Component() = default;

    /* Component Cycle */
    // 수정중 
    virtual void OnEnable() = 0;    // GameObject의 모든 Compoent가 생성된 뒤 초기화로 호출
    virtual void OnDestroy() = 0;   // GameObject가 파괴되거나, 컴포넌트가 파괴될 때 호출
};

