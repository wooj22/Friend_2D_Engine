#include "BoxCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "Script.h"
#include "RenderSystem.h"
#include "DebugGizmo.h"

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

void BoxCollider::FinalizeCollision()
{
    // Enter & Stay
    for (ICollider* other : currentFrameCollisions)
    {
        if (lastFrameCollisions.find(other) == lastFrameCollisions.end())
        {
            // Enter
            if (isTrigger || other->isTrigger)
                OnTriggerEnter(other);
            else
                OnCollisionEnter(other);
        }
        else
        {
            // Stay
            if (isTrigger || other->isTrigger)
                OnTriggerStay(other);
            else
                OnCollisionStay(other);
        }
    }

    // Exit
    for (ICollider* other : lastFrameCollisions)
    {
        if (currentFrameCollisions.find(other) == currentFrameCollisions.end())
        {
            if (isTrigger || other->isTrigger)
                OnTriggerExit(other);
            else
                OnCollisionExit(other);
        }
    }

    // Swap
    lastFrameCollisions = currentFrameCollisions;
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

void BoxCollider::OnCollisionStay(ICollider* other)
{
    // script
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnCollisionStay(other);
}

void BoxCollider::OnCollisionExit(ICollider* other)
{
    // script
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnCollisionExit(other);
}


void BoxCollider::OnTriggerEnter(ICollider* other)
{
    // script
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnTriggerEnter(other);
}

void BoxCollider::OnTriggerStay(ICollider* other)
{
    // script
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnTriggerStay(other);
}

void BoxCollider::OnTriggerExit(ICollider* other)
{
    // script
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnTriggerExit(other);
}

bool BoxCollider::CheckAABB(BoxCollider* other)
{
    // this transform 정보
    const Vector2 posA = transform->GetPosition() + Vector2(offset.x, -offset.y);
    const Vector2 scaleA = transform->GetScale();

    // 컴포넌트별 곱 직접 작성
    Vector2 scaledSizeA = Vector2(size.x * scaleA.x, size.y * scaleA.y);
    Vector2 halfSizeA = scaledSizeA * 0.5f;

    // other transform 정보
    const Vector2 posB = other->transform->GetPosition() + Vector2(other->offset.x, -other->offset.y);
    const Vector2 scaleB = other->transform->GetScale();

    Vector2 scaledSizeB = Vector2(other->size.x * scaleB.x, other->size.y * scaleB.y);
    Vector2 halfSizeB = scaledSizeB * 0.5f;

    // AABB 충돌 검사 (std::abs 사용)
    bool collisionX = std::abs(posA.x - posB.x) <= (halfSizeA.x + halfSizeB.x);
    bool collisionY = std::abs(posA.y - posB.y) <= (halfSizeA.y + halfSizeB.y);

    return collisionX && collisionY;
}

void BoxCollider::DebugColliderDraw()
{
    // localRect에 offset 직접 반영 (y 축 반전 포함)
    float left = -size.x * 0.5f + offset.x;
    float right = size.x * 0.5f + offset.x;
    float top = -size.y * 0.5f - offset.y;
    float bottom = size.y * 0.5f - offset.y;
    D2D1_RECT_F localRect = D2D1::RectF(left, top, right, bottom);

    // offsetMatrix 없이 offset을 localRect에 더했으니 transform 행렬만 곱함
    auto finalMatrix = transform->GetScreenMatrix();

    RenderSystem::Get().DrawRect(localRect, finalMatrix);
}