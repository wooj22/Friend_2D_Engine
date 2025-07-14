#include "BoxCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "Script.h"
#include "RenderSystem.h"
#include "DebugGizmo.h"
#include "CircleCollider.h"

void BoxCollider::OnEnable()
{
    transform = this->owner->GetComponent<Transform>();
}

void BoxCollider::OnDestroy()
{

}

bool BoxCollider::isCollision(ICollider* other)
{
    if (other->colliderType == ColliderType::Box)
    {
        return CheckAABBCollision(static_cast<BoxCollider*>(other));
    }
    else if (other->colliderType == ColliderType::Circle)
    {
        return CheakCircleCollision(static_cast<CircleCollider*>(other));
    }

    return false;
}

bool BoxCollider::CheckAABBCollision(BoxCollider* other)
{
    // this transform
    const Vector2 posA = transform->GetPosition() + offset;
    const Vector2 scaleA = transform->GetScale();

    Vector2 scaledSizeA(size.x * scaleA.x, size.y * scaleA.y);
    Vector2 halfSizeA = scaledSizeA * 0.5f;

    // other transform
    const Vector2 posB = other->transform->GetPosition() + other->offset;
    const Vector2 scaleB = other->transform->GetScale();

    Vector2 scaledSizeB(other->size.x * scaleB.x, other->size.y * scaleB.y);
    Vector2 halfSizeB = scaledSizeB * 0.5f;

    // AABB collision cheak
    bool collisionX = std::abs(posA.x - posB.x) <= (halfSizeA.x + halfSizeB.x);
    bool collisionY = std::abs(posA.y - posB.y) <= (halfSizeA.y + halfSizeB.y);

    return collisionX && collisionY;
}

bool BoxCollider::CheakCircleCollision(CircleCollider* other)
{
    // 박스 중심 위치 (offset.y 반전 적용)
    Vector2 boxPos = transform->GetPosition() + Vector2(offset.x, -offset.y);
    Vector2 boxScale = transform->GetScale();
    Vector2 boxHalfSize = (size * boxScale) * 0.5f;

    // 원 중심 위치 (offset.y 반전 적용)
    Vector2 circlePos = other->transform->GetPosition() + Vector2(other->offset.x, -other->offset.y);
    float circleRadius = other->radius; // scale 무시하거나 필요하면 곱함

    // 원 중심에서 박스 좌표계를 기준으로 상대 위치 구하기
    Vector2 diff = circlePos - boxPos;

    // 박스 내부에 점을 클램핑 (박스 경계 내로)
    float closestX = clamp(diff.x, -boxHalfSize.x, boxHalfSize.x);
    float closestY = clamp(diff.y, -boxHalfSize.y, boxHalfSize.y);

    // 클램핑된 점과 원 중심 간 거리 계산
    Vector2 closestPoint = boxPos + Vector2(closestX, closestY);
    Vector2 distanceVec = circlePos - closestPoint;

    float distanceSq = distanceVec.x * distanceVec.x + distanceVec.y * distanceVec.y;

    return distanceSq <= (circleRadius * circleRadius);
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

void BoxCollider::OnCollisionEnter(ICollider* other)
{
    // Block
    transform->SetPosition(transform->prePosition);

    // script
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnCollisionEnter(other);
}

void BoxCollider::OnCollisionStay(ICollider* other)
{
    // Block
    transform->SetPosition(transform->prePosition);

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

void BoxCollider::DebugColliderDraw()
{
    float left = -size.x * 0.5f + offset.x;
    float right = size.x * 0.5f + offset.x;
    float top = -size.y * 0.5f - offset.y;
    float bottom = size.y * 0.5f - offset.y;
    D2D1_RECT_F localRect = D2D1::RectF(left, top, right, bottom);

    RenderSystem::Get().DrawRect(localRect, transform->GetScreenMatrix());
}