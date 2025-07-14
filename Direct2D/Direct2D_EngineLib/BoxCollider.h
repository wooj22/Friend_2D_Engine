#pragma once
#include "ICollider.h"
#include "ColliderSystem.h"

/* [BoxCollider Component]
* 
*/

class Transform;
class BoxCollider : public ICollider
{
public:
    Transform* transform;
    Vector2 offset = Vector2::zero;
    Vector2 size = Vector2::one;
    //bool isTrigger = false;             // ICollider
    
public:
    // component cycle
    BoxCollider() { ColliderSystem::Get().Regist(this); }
    ~BoxCollider() override { ColliderSystem::Get().Unregist(this); }
    void OnEnable() override;
    bool isCollision(ICollider* other) override;
    void OnDestroy() override;

    // collision event
    void OnCollisionEnter(ICollider* other);
    void OnTriggerEnter(ICollider* other);

private:
    bool CheckAABB(BoxCollider* other);
};


