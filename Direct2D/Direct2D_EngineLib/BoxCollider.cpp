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

// UpdateBounds()
// box collider의 aabb bound를 update한다
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

// isCollision()
// 넘겨받은 콜라이더의 타입에 따른 충돌 결과를 return한다
// 충돌한 경우 contact info를 계산한다
bool BoxCollider::isCollision(ICollider* other, ContactInfo& contact)
{
    if (!transform) return false;

    if (other->colliderType == ColliderType::Box)
    {
        return CheckAABBCollision(static_cast<BoxCollider*>(other), contact);
    }
    else if (other->colliderType == ColliderType::Circle)
    {
        return CheckCircleCollision(static_cast<CircleCollider*>(other), contact);
    }

    return false;
}

// CheckAABBCollision()
// this box와 other box의 aabb 충돌 체크
bool BoxCollider::CheckAABBCollision(BoxCollider* other, ContactInfo& contact)
{
    // 1. AABB 겹침 체크
    if (maxX < other->minX || minX > other->maxX || maxY < other->minY || minY > other->maxY)
        return false;

    // 2. 충돌 지점: 두 AABB 중심 중간점
    Vector2 thisCenter = GetCenter();
    Vector2 otherCenter = other->GetCenter();
    contact.point = (thisCenter + otherCenter) * 0.5f;

    // 3. 축별 침투 깊이 계산
    float overlapX = min(maxX, other->maxX) -max(minX, other->minX);
    float overlapY = min(maxY, other->maxY) - max(minY, other->minY);

    // 4. 침투가 적은 축을 따라 법선 결정
    if (overlapX < overlapY)
    {
        // X축 방향 법선
        contact.normal = (thisCenter.x < otherCenter.x) ? Vector2(-1, 0) : Vector2(1, 0);
    }
    else
    {
        // Y축 방향 법선
        contact.normal = (thisCenter.y < otherCenter.y) ? Vector2(0, -1) : Vector2(0, 1);
    }

    return true;
}

// CheckCircleCollision()
// this box와 other circle의 충돌 체크
bool BoxCollider::CheckCircleCollision(CircleCollider* other, ContactInfo& contact)
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
    contact.point = closestPoint;

    // 충돌 법선 (원 중심에서 박스 경계점 방향)
    if (distSq == 0.0f)
    {
        // 중심이 박스 안에 완전히 들어갔을 때 (예외처리)
        // 임의로 위쪽 방향 지정
        contact.normal = Vector2(0, 1);
    }
    else
    {
        contact.normal = diff.Normalized();
    }

    return true;
}

// FinalizeCollision()
// 이전 프레임 충돌 정보와 현재 프레임 충돌 정보를 비교하여
// isTrigger 유무에 따라 Enter, Stay, Exit 충돌 이벤트 함수를 호출한다.
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

void BoxCollider::OnCollisionEnter(ICollider* other, ContactInfo& contact)
{
    Vector2 pos = transform->GetPosition();
    Vector2 prePos = transform->prePosition;

    // 축별 보정
    if (contact.normal.x != 0) { pos.x = prePos.x; }
    if (contact.normal.y != 0) { pos.y = prePos.y; }
    transform->SetPosition(pos);

    // script
    auto scripts = owner->GetComponents<Script>();
    for (auto s : scripts)
        s->OnCollisionEnter(other);
}

void BoxCollider::OnCollisionStay(ICollider* other, ContactInfo& contact)
{
    Vector2 pos = transform->GetPosition();
    Vector2 prePos = transform->prePosition;

    // 축별 보정
    if (contact.normal.x != 0) { pos.x = prePos.x; }
    if (contact.normal.y != 0) { pos.y = prePos.y; }
    transform->SetPosition(pos);

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