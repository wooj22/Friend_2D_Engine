#pragma once
#include "Component.h"
#include "PhysicsSystem.h"
#include "Vector2.h"

/* [Rigidbody Component]
* 
*/

class Transform;
class Rigidbody : public Component
{
private:
    Transform* transform = nullptr;

public:
    Vector2 velocity = Vector2::zero;           // 속력
    Vector2 acceleration = Vector2::zero;       // 가속도
    float mass = 1.0f;                          // 질량
    bool useGravity = true;                     // 중력 사용 여부
    float gravityScale = 10.0f;                 // 중력 보정ㄴ
    float drag = 0.0f;

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
    void FixedUpdate();
    void OnDestroy() override;

public:
    // func
    void AddForce(const Vector2& force);
};


