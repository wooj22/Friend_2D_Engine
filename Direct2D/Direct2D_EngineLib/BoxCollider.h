#pragma once
#include "Component.h"
#include "ColliderSystem.h"

/* [Animator Component]
* 
*/

class BoxCollider : public Component
{
public:
    // component cycle
    BoxCollider()
    {
        ColliderSystem::Get().Regist(this);
    }
    ~BoxCollider() override
    {
        ColliderSystem::Get().Unregist(this);
    }

    void OnEnable() override;
    void Update();
    void OnDestroy() override;
};


