#pragma once
#include "Component.h"
#include "PhysicsSystem.h"

/* [Rigidbody Component]
* 
*/

class Rigidbody : public Component
{
public:
    // component cycle
    Rigidbody()
    {
        PhysicsSystem::Get().Regist(this);
    }
    ~Rigidbody() override
    {
        PhysicsSystem::Get().Unregist(this);
    }

    void OnEnable() override;
    void Update();
    void OnDestroy() override;
};


