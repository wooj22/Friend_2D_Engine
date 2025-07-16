#include "BoxCollider.h"
#include "GameObject.h"
#include "Transform.h"
#include "Script.h"
#include "RenderSystem.h"
#include "DebugGizmo.h"
#include "CircleCollider.h"
#include "Rigidbody.h"

void BoxCollider::OnEnable()
{
    transform = this->owner->GetComponent<Transform>();
}

void BoxCollider::OnDestroy()
{

}

void BoxCollider::UpdateBounds()
{
    Vector2 pos = transform->GetPosition() + offset;
    Vector2 scale = transform->GetScale();
    Vector2 scaledSize(size.x * scale.x, size.y * scale.y);
    Vector2 halfSize = scaledSize * 0.5f;

    minX = pos.x - halfSize.x;
    maxX = pos.x + halfSize.x;
    minY = pos.y - halfSize.y;
    maxY = pos.y + halfSize.y;
}

bool BoxCollider::isCollision(ICollider* other, ContactInfo& outContact)
{
    if (!transform) return false;

    if (other->colliderType == ColliderType::Box)
    {
        return CheckAABBCollision(static_cast<BoxCollider*>(other), outContact);
    }
    else if (other->colliderType == ColliderType::Circle)
    {
        return CheckCircleCollision(static_cast<CircleCollider*>(other), outContact);
    }

    return false;
}

bool BoxCollider::CheckAABBCollision(BoxCollider* other, ContactInfo& outContact)
{
    // 1. AABB 겹침 체크
    if (maxX < other->minX || minX > other->maxX || maxY < other->minY || minY > other->maxY)
        return false;

    // 2. 충돌 지점: 두 AABB 중심 중간점
    Vector2 thisCenter = GetCenter();
    Vector2 otherCenter = other->GetCenter();
    outContact.point = (thisCenter + otherCenter) * 0.5f;

    // 3. 축별 침투 깊이 계산
    float overlapX = min(maxX, other->maxX) -max(minX, other->minX);
    float overlapY = min(maxY, other->maxY) - max(minY, other->minY);

    // 4. 침투가 적은 축을 따라 법선 결정
    if (overlapX < overlapY)
    {
        // X축 방향 법선
        outContact.normal = (thisCenter.x < otherCenter.x) ? Vector2(-1, 0) : Vector2(1, 0);
    }
    else
    {
        // Y축 방향 법선
        outContact.normal = (thisCenter.y < otherCenter.y) ? Vector2(0, -1) : Vector2(0, 1);
    }

    return true;
}

bool BoxCollider::CheckCircleCollision(CircleCollider* other, ContactInfo& outContact)
{
    Vector2 boxPos = transform->GetPosition() + offset;
    Vector2 boxScale = transform->GetScale();
    Vector2 boxSizeScaled(size.x * boxScale.x, size.y * boxScale.y);
    Vector2 halfBoxSize = boxSizeScaled * 0.5f;

    Vector2 circlePos = other->transform->GetPosition() + other->offset;
    Vector2 circleScale = other->transform->GetScale();
    float circleRadius = other->radius * circleScale.x;

    // AABB 내부 가장 가까운 점(clamp)
    float closestX = clamp(circlePos.x, boxPos.x - halfBoxSize.x, boxPos.x + halfBoxSize.x);
    float closestY = clamp(circlePos.y, boxPos.y - halfBoxSize.y, boxPos.y + halfBoxSize.y);

    Vector2 closestPoint(closestX, closestY);

    // 원 중심과 가장 가까운 점 거리 제곱 계산
    Vector2 diff = circlePos - closestPoint;
    float distSq = diff.SqrMagnitude();

    // 충돌 여부
    if (distSq > circleRadius * circleRadius)
        return false;

    // 충돌 지점
    outContact.point = closestPoint;

    // 충돌 법선 (원 중심에서 박스 경계점 방향)
    if (distSq == 0.0f)
    {
        // 중심이 박스 안에 완전히 들어갔을 때 (예외처리)
        // 임의로 위쪽 방향 지정
        outContact.normal = Vector2(0, 1);
    }
    else
    {
        outContact.normal = diff.Normalized();
    }

    return true;
}

//bool BoxCollider::InternalCheckCollision(ICollider* other)
//{
//    if (other->colliderType == ColliderType::Box)
//        return CheckAABBCollision(static_cast<BoxCollider*>(other));
//    else if (other->colliderType == ColliderType::Circle)
//        return CheakCircleCollision(static_cast<CircleCollider*>(other));
//
//    return false;
//}

void BoxCollider::FinalizeCollision()
{
    // Enter & Stay
    for (auto& pair : currentFrameCollisions)
    {
        ICollider* other = pair.first;
        ContactInfo& contact = pair.second;

        if (lastFrameCollisions.find(other) == lastFrameCollisions.end())
        {
            if (isTrigger || other->isTrigger)
                OnTriggerEnter(other);
            else
                OnCollisionEnter(other, contact);
        }
        else
        {
            if (isTrigger || other->isTrigger)
                OnTriggerStay(other);
            else
                OnCollisionStay(other, contact);
        }
    }

    // Exit
    for (auto& pair : lastFrameCollisions)
    {
        ICollider* other = pair.first;

        if (currentFrameCollisions.find(other) == currentFrameCollisions.end())
        {
            if (isTrigger || other->isTrigger)
                OnTriggerExit(other);
            else
                OnCollisionExit(other);
        }
    }

    lastFrameCollisions = currentFrameCollisions;
    currentFrameCollisions.clear();
}

void BoxCollider::OnCollisionEnter(ICollider* other, ContactInfo& outContact)
{
    // Block
    //transform->SetPosition(transform->prePosition.x, transform->prePosition.y);   // top view
    transform->SetPosition(transform->GetPosition().x, transform->prePosition.y);   // gravity

    // script
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnCollisionEnter(other);
}

void BoxCollider::OnCollisionStay(ICollider* other, ContactInfo& outContact)
{
    // Block
    //transform->SetPosition(transform->prePosition.x, transform->prePosition.y);   // top view
    transform->SetPosition(transform->GetPosition().x, transform->prePosition.y);   // gravity

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

Vector2 BoxCollider::GetCenter() const
{
    // transform 위치 + offset + size의 절반 (중심)
    return transform->GetPosition() + offset + (size * 0.5f);
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