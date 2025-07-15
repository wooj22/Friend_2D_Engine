#pragma once
#include "ICollider.h"
#include "ColliderSystem.h"

/* [BoxCollider Component]
* 
*/

class Transform;
class CircleCollider;
class BoxCollider : public ICollider
{
public:
    Transform* transform = nullptr;

    // collider
    Vector2 offset = Vector2::zero;
    Vector2 size = { 10,10 };
    
public:
    // component cycle
    BoxCollider() 
    { 
        colliderType = ColliderType::Box;
        ColliderSystem::Get().Regist(this);
    }
    ~BoxCollider() override { ColliderSystem::Get().Unregist(this); }

    void OnEnable() override;
    void UpdateBounds() override;
    bool isCollision(ICollider* other) override;
    void FinalizeCollision() override;
    void OnDestroy() override;

private:
    // collision event
    void OnCollisionEnter(ICollider* other) override;
    void OnCollisionStay(ICollider* other) override;
    void OnCollisionExit(ICollider* other) override;
    void OnTriggerEnter(ICollider* other) override;
    void OnTriggerStay(ICollider* other) override;
    void OnTriggerExit(ICollider* other) override;

    // collisio cheak
    bool CheckAABBCollision(BoxCollider* other);
    bool CheakCircleCollision(CircleCollider* other);

public:
    // debug draw
    void DebugColliderDraw() override;
};


