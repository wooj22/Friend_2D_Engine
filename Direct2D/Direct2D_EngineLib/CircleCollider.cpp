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

bool CircleCollider::isCollision(ICollider* other)
{
    if (!transform) return false;

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

    float scaledRadiusA = radius * scaleA.x; // xÃà ±âÁØ
    float scaledRadiusB = other->radius * scaleB.x;

    float distSq = (posA - posB).SqrMagnitude();
    float radiusSum = scaledRadiusA + scaledRadiusB;

    return distSq <= radiusSum * radiusSum;
}

bool CircleCollider::CheakBoxCollision(BoxCollider* other)
{
    Vector2 circlePos = transform->GetPosition() + offset;
    Vector2 boxPos = other->transform->GetPosition() + other->offset;
    Vector2 boxHalfSize = other->size * 0.5f * other->transform->GetScale();

    float radiusScaled = radius * transform->GetScale().x;

    float closestX = clamp(circlePos.x, boxPos.x - boxHalfSize.x, boxPos.x + boxHalfSize.x);
    float closestY = clamp(circlePos.y, boxPos.y - boxHalfSize.y, boxPos.y + boxHalfSize.y);

    float distX = circlePos.x - closestX;
    float distY = circlePos.y - closestY;

    return (distX * distX + distY * distY) <= (radiusScaled * radiusScaled);
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
    // Block
    //transform->SetPosition(transform->GetPosition().x, transform->prePosition.y);
    transform->SetPosition(transform->prePosition.x, transform->prePosition.y);
    
    // script
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnCollisionEnter(other);
}

void CircleCollider::OnCollisionStay(ICollider* other)
{
    // Block
    //transform->SetPosition(transform->GetPosition().x, transform->prePosition.y);
    transform->SetPosition(transform->prePosition.x, transform->prePosition.y);

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