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
    Vector2 scale = transform->GetScale();
    float scaledRadius = radius * scale.x;  // Circle은 x축만 쓰는 관행

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

    float scaledRadiusA = radius * scaleA.x; // x축 기준
    float scaledRadiusB = other->radius * scaleB.x;

    float distSq = (posA - posB).SqrMagnitude();
    float radiusSum = scaledRadiusA + scaledRadiusB;

    return distSq <= radiusSum * radiusSum;
}

bool CircleCollider::CheakBoxCollision(BoxCollider* other)
{
    return false;
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
    transform->SetPosition(transform->GetPosition().x, transform->prePosition.y);

    // script
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnCollisionEnter(other);
}

void CircleCollider::OnCollisionStay(ICollider* other)
{
    // Block
    transform->SetPosition(transform->GetPosition().x, transform->prePosition.y);

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