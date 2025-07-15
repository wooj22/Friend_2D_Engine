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

bool BoxCollider::isCollision(ICollider* other)
{
    if (!transform) return false;

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
    bool overlapX = !(maxX < other->minX || minX > other->maxX);
    bool overlapY = !(maxY < other->minY || minY > other->maxY);

    return overlapX && overlapY;
}

bool BoxCollider::CheakCircleCollision(CircleCollider* other)
{
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

void BoxCollider::OnCollisionEnter(ICollider* other)
{
    // Block
    transform->SetPosition(transform->GetPosition().x, transform->prePosition.y);

    // script
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnCollisionEnter(other);
}

void BoxCollider::OnCollisionStay(ICollider* other)
{
    // Block
    transform->SetPosition(transform->GetPosition().x, transform->prePosition.y);

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