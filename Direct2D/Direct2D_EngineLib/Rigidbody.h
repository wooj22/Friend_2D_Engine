#pragma once
#include "Component.h"
#include "PhysicsSystem.h"
#include "Vector2.h"

/* [Rigidbody Component]
* 물리 게산을 담당하는 컴포넌트로, Transform을 참조하여 이동시킨다.
* 속도, 가속도, 질량, 중력, 공기 저항 등의 물리 속성을 관리하며
* PhysicsSystem에 등록되어 FixedUpdate()주기로 로직을 처리한다.
*/

class Transform;
class Rigidbody : public Component
{
private:
    Transform* transform = nullptr;

public:
    Vector2 velocity = Vector2::zero;           // 속도
    Vector2 acceleration = Vector2::zero;       // 가속도
    float mass = 1.0f;                          // 질량
    bool useGravity = true;                     // 중력 사용 여부
    float gravityScale = 50.0f;                 // 중력 보정값
    float drag = 0.0f;                          // 공기 저항, 마찰력 (클수록 속도 깎임)

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


