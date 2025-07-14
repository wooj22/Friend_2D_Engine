#pragma once
#include "ICollider.h"
#include "ColliderSystem.h"

/* [CircleCollider Component]
*
*/

class Transform;
class BoxCollider;
class CircleCollider : public ICollider
{
public:
    Transform* transform;
    Vector2 offset = Vector2::zero;
    float radius = 1.0f;
    //bool isTrigger = false;             // ICollider

public:
    // component cycle
    CircleCollider() { ColliderSystem::Get().Regist(this); }
    ~CircleCollider() override { ColliderSystem::Get().Unregist(this); }

    void OnEnable() override;
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

    // collistion cheak
    bool CheckCircleCollision(CircleCollider* other);
    bool CheakBoxCollision(BoxCollider* other);

public:
    // debug draw
    void DebugColliderDraw() override;
};

