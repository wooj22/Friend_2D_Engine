#include "CircleCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "Script.h"
#include "RenderSystem.h"
#include "DebugGizmo.h"
#include "BoxCollider.h"

void CircleCollider::OnEnable()
{
    transform = owner->GetComponent<Transform>();
}

void CircleCollider::OnDestroy()
{

}

bool CircleCollider::isCollision(ICollider* other)
{
    if (other->colliderType == ColliderType::Circle)
    {
        return CheckCircleCollision(static_cast<CircleCollider*>(other));
    }
    else if (other->colliderType == ColliderType::Box)
    {
        return CheakBoxCollision(static_cast<BoxCollider*>(other));
    }

    return false;
}

bool CircleCollider::CheckCircleCollision(CircleCollider* other)
{
    Vector2 posA = transform->GetPosition() + offset;
    Vector2 posB = other->transform->GetPosition() + other->offset;

    Vector2 scaleA = transform->GetScale();
    Vector2 scaleB = other->transform->GetScale();

    float scaledRadiusA = radius * scaleA.x; // x축 기준
    float scaledRadiusB = other->radius * scaleB.x;

    float distSq = (posA - posB).SqrMagnitude();
    float radiusSum = scaledRadiusA + scaledRadiusB;

    return distSq <= radiusSum * radiusSum;
}

bool CircleCollider::CheakBoxCollision(BoxCollider* other)
{
    // 박스 중심 위치 (offset.y 반전 적용)
    Vector2 boxPos = other->transform->GetPosition() + Vector2(other->offset.x, -other->offset.y);
    Vector2 boxScale = other->transform->GetScale();
    Vector2 boxHalfSize = (other->size * boxScale) * 0.5f;

    // 원 중심 위치 (offset.y 반전 적용)
    Vector2 circlePos = transform->GetPosition() + Vector2(offset.x, -offset.y);
    float circleRadius = radius;  // 필요하면 scale 무시

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

void CircleCollider::FinalizeCollision()
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

void CircleCollider::OnCollisionEnter(ICollider* other)
{
    transform->SetPosition(transform->prePosition);

    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnCollisionEnter(other);
}

void CircleCollider::OnCollisionStay(ICollider* other)
{
    transform->SetPosition(transform->prePosition);

    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnCollisionStay(other);
}

void CircleCollider::OnCollisionExit(ICollider* other)
{
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnCollisionExit(other);
}

void CircleCollider::OnTriggerEnter(ICollider* other)
{
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnTriggerEnter(other);
}

void CircleCollider::OnTriggerStay(ICollider* other)
{
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnTriggerStay(other);
}

void CircleCollider::OnTriggerExit(ICollider* other)
{
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnTriggerExit(other);
}

void CircleCollider::DebugColliderDraw()
{
    Vector2 scale = transform->GetScale();
    float scaledRadius = radius * scale.x;

    Vector2 pos = transform->GetPosition() + Vector2(offset.x, -offset.y);

    D2D1_ELLIPSE ellipse = D2D1::Ellipse(
        D2D1::Point2F(pos.x, pos.y),
        scaledRadius,
        scaledRadius
    );

    RenderSystem::Get().DrawCircle(ellipse, transform->GetScreenMatrix());
}