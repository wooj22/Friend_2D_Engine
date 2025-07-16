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

void CircleCollider::UpdateBounds()
{
    Vector2 pos = transform->GetPosition() + offset;
    float scaledRadius = radius * transform->GetScale().x;

    minX = pos.x - scaledRadius;
    maxX = pos.x + scaledRadius;
    minY = pos.y - scaledRadius;
    maxY = pos.y + scaledRadius;
}

bool CircleCollider::isCollision(ICollider* other, ContactInfo& outContact)
{
    if (!transform) return false;

    if (other->colliderType == ColliderType::Circle)
    {
        return CheckCircleCollision(static_cast<CircleCollider*>(other), outContact);
    }
    else if (other->colliderType == ColliderType::Box)
    {
        return CheckBoxCollision(static_cast<BoxCollider*>(other), outContact);
    }

    return false;
}

bool CircleCollider::CheckCircleCollision(CircleCollider* other, ContactInfo& outContact)
{
    Vector2 posA = transform->GetPosition() + offset;
    Vector2 posB = other->transform->GetPosition() + other->offset;

    Vector2 scaleA = transform->GetScale();
    Vector2 scaleB = other->transform->GetScale();

    float scaledRadiusA = radius * scaleA.x;
    float scaledRadiusB = other->radius * scaleB.x;

    Vector2 diff = posA - posB;
    float distSq = diff.SqrMagnitude();
    float radiusSum = scaledRadiusA + scaledRadiusB;

    if (distSq > radiusSum * radiusSum)
        return false;

    // Contact Info
    Vector2 dir;
    if (distSq == 0.0f)
        dir = Vector2(1, 0); // 예외처리 (완전히 겹쳤을 때)
    else
        dir = diff.Normalized();

    outContact.normal = dir;
    outContact.point = posB + dir * scaledRadiusB;

    return true;
}

bool CircleCollider::CheckBoxCollision(BoxCollider* other, ContactInfo& outContact)
{
    Vector2 circlePos = transform->GetPosition() + offset;
    Vector2 circleScale = transform->GetScale();
    float radiusScaled = radius * circleScale.x;

    Vector2 boxPos = other->transform->GetPosition() + other->offset;
    Vector2 boxScale = other->transform->GetScale();
    Vector2 boxSizeScaled = other->size * boxScale;
    Vector2 halfBoxSize = boxSizeScaled * 0.5f;

    // Clamp point 계산
    float closestX = clamp(circlePos.x, boxPos.x - halfBoxSize.x, boxPos.x + halfBoxSize.x);
    float closestY = clamp(circlePos.y, boxPos.y - halfBoxSize.y, boxPos.y + halfBoxSize.y);

    Vector2 closestPoint(closestX, closestY);
    Vector2 diff = circlePos - closestPoint;

    float distSq = diff.SqrMagnitude();

    if (distSq > radiusScaled * radiusScaled)
        return false;

    // Contact Info
    outContact.point = closestPoint;

    if (distSq == 0.0f)
    {
        // 중심이 박스 내부에 완전히 들어간 경우, 예외처리
        outContact.normal = Vector2(0, 1);
    }
    else
    {
        outContact.normal = diff.Normalized();
    }

    return true;
}

//bool CircleCollider::InternalCheckCollision(ICollider* other)
//{
//    if (other->colliderType == ColliderType::Box)
//        return CheakBoxCollision(static_cast<BoxCollider*>(other));
//    else if (other->colliderType == ColliderType::Circle)
//        return CheckCircleCollision(static_cast<CircleCollider*>(other));
//
//    return false;
//}

void CircleCollider::FinalizeCollision()
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

void CircleCollider::OnCollisionEnter(ICollider* other, ContactInfo& outContact)
{
    // Block
    //transform->SetPosition(transform->prePosition.x, transform->prePosition.y);   // top view
    transform->SetPosition(transform->GetPosition().x, transform->prePosition.y);   // gravity
    
    // script
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnCollisionEnter(other);
}

void CircleCollider::OnCollisionStay(ICollider* other, ContactInfo& outContact)
{
    // Block
    //transform->SetPosition(transform->prePosition.x, transform->prePosition.y);   // top view
    transform->SetPosition(transform->GetPosition().x, transform->prePosition.y);   // gravity

    // script
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
    // script
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnTriggerEnter(other);
}

void CircleCollider::OnTriggerStay(ICollider* other)
{
    // script
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnTriggerStay(other);
}

void CircleCollider::OnTriggerExit(ICollider* other)
{
    // script
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnTriggerExit(other);
}

void CircleCollider::DebugColliderDraw()
{
    Vector2 localPos = Vector2(offset.x, -offset.y);

    D2D1_ELLIPSE ellipse = D2D1::Ellipse(
        D2D1::Point2F(localPos.x, localPos.y),
        radius,
        radius
    );

    RenderSystem::Get().DrawCircle(ellipse, transform->GetScreenMatrix());
}