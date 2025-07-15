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
    Vector2 boxPos = transform->GetPosition() + offset;
    Vector2 boxScale = transform->GetScale();
    Vector2 boxSizeScaled(size.x * boxScale.x, size.y * boxScale.y);
    Vector2 halfBoxSize = boxSizeScaled * 0.5f;

    Vector2 circlePos = other->transform->GetPosition() + other->offset;
    Vector2 circleScale = other->transform->GetScale();
    float circleRadius = other->radius * circleScale.x;

    // AABB clamp point 찾기
    float closestX = clamp(circlePos.x, boxPos.x - halfBoxSize.x, boxPos.x + halfBoxSize.x);
    float closestY = clamp(circlePos.y, boxPos.y - halfBoxSize.y, boxPos.y + halfBoxSize.y);

    Vector2 closestPoint(closestX, closestY);

    // 거리 계산
    float distSq = (circlePos - closestPoint).SqrMagnitude();

    return distSq <= circleRadius * circleRadius;
}

bool BoxCollider::InternalCheckCollision(ICollider* other)
{
    if (other->colliderType == ColliderType::Box)
        return CheckAABBCollision(static_cast<BoxCollider*>(other));
    else if (other->colliderType == ColliderType::Circle)
        return CheakCircleCollision(static_cast<CircleCollider*>(other));

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
    //transform->SetPosition(transform->prePosition.x, transform->prePosition.y);   // top view
    transform->SetPosition(transform->GetPosition().x, transform->prePosition.y);   // gravity

    // TODO :: 축별 이동 제한 로직 추가
    //float deltaX = transform->GetPosition().x - transform->prePosition.x;
    //float deltaY = transform->GetPosition().y - transform->prePosition.y;

    //Vector2 tryX = Vector2(transform->prePosition.x + deltaX, transform->prePosition.y);
    //Vector2 tryY = Vector2(transform->prePosition.x, transform->prePosition.y + deltaY);

    //auto rb = owner->GetComponent<Rigidbody>();
 
    //// x축
    //transform->SetPosition(tryX);
    //if (InternalCheckCollision(other))
    //{
    //    if (rb) { rb->blockX = true; }
    //    deltaX = 0;
    //}

    //// y
    //transform->SetPosition(tryY);
    //if (InternalCheckCollision(other))
    //{
    //    if (rb) { rb->blockY = true; }
    //    deltaY = 0;
    //}

    // script
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnCollisionEnter(other);
}

void BoxCollider::OnCollisionStay(ICollider* other)
{
    // Block
    //transform->SetPosition(transform->prePosition.x, transform->prePosition.y);   // top view
    transform->SetPosition(transform->GetPosition().x, transform->prePosition.y);   // gravity

    // TODO :: 축별 이동 제한 로직 추가
    //float deltaX = transform->GetPosition().x - transform->prePosition.x;
    //float deltaY = transform->GetPosition().y - transform->prePosition.y;

    //Vector2 tryX = Vector2(transform->prePosition.x + deltaX, transform->prePosition.y);
    //Vector2 tryY = Vector2(transform->prePosition.x, transform->prePosition.y + deltaY);

    //auto rb = owner->GetComponent<Rigidbody>();

    //// x축
    //transform->SetPosition(tryX);
    //if (InternalCheckCollision(other))
    //{
    //    if (rb) { rb->blockX = true; }
    //    deltaX = 0;
    //}

    //// y
    //transform->SetPosition(tryY);
    //if (InternalCheckCollision(other))
    //{
    //    if (rb) { rb->blockY = true; }
    //    deltaY = 0;
    //}

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