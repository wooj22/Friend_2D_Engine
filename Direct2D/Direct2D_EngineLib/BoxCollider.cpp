#include "BoxCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "Script.h"

void BoxCollider::OnEnable()
{
    transform = this->owner->GetComponent<Transform>();
}

bool BoxCollider::isCollision(ICollider* other)
{
    if (other->colliderType == ColliderType::Box)
    {
        return CheckAABB(static_cast<BoxCollider*>(other));
    }
    else if (other->colliderType == ColliderType::Circle)
    {
        // TODO :: circle collider
    }

    return false;
}

void BoxCollider::OnDestroy()
{
    
}

void BoxCollider::OnCollisionEnter(ICollider* other)
{
    // 이전 위치로 이동

    // script
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnCollisionEnter(other);
}

void BoxCollider::OnTriggerEnter(ICollider* other)
{
    // script
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnCollisionEnter(other);
}

bool BoxCollider::CheckAABB(BoxCollider* other)
{
    // this의 실제 위치 계산
    Vector2 posA = transform->GetPosition() + offset;
    Vector2 halfSizeA = size * 0.5f;

    // other의 실제 위치 계산
    Vector2 posB = other->transform->GetPosition() + other->offset;
    Vector2 halfSizeB = other->size * 0.5f;

    // AABB 충돌 검사
    bool collisionX = fabs(posA.x - posB.x) <= (halfSizeA.x + halfSizeB.x);
    bool collisionY = fabs(posA.y - posB.y) <= (halfSizeA.y + halfSizeB.y);

    return collisionX && collisionY;
}

