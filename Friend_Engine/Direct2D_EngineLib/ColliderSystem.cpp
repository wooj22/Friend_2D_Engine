#include "ColliderSystem.h"
#include <algorithm>
#include "ICollider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

// component ���
void ColliderSystem::Regist(ICollider* component)
{
    pending_components.push_back(component);
}

// component ��� ����
void ColliderSystem::Unregist(ICollider* component)
{
    // delete
    for (auto it = components.begin(); it != components.end(); ++it) {
        if (*it == component) {
            components.erase(it);
            return;
        }
    }

    // pending delete
    for (auto it = pending_components.begin(); it != pending_components.end(); ++it) {
        if (*it == component) {
            pending_components.erase(it);
            return;
        }
    }
}

// component system
void ColliderSystem::FixedUpdate()
{
    // pending_components push
    for (ICollider* collider : pending_components)
    {
        components.push_back(collider);
    }
    pending_components.clear();

	// update bounds
    for (auto collider : components)
    {
        collider->currentFrameCollisions.clear();   // curent frame collision data reset
        collider->UpdateBounds();                   // update bounds
    }

    // Sweep and Prune - SweepandPruneOverlapCheck
    // minX sort
    std::sort(components.begin(), components.end(), [](ICollider* a, ICollider* b)
        { return a->minX < b->minX; });

    // collision cheak
    for (size_t i = 0; i < components.size(); ++i)
    {
        ICollider* a = components[i];
        for (size_t j = i + 1; j < components.size(); ++j)
        {
            ICollider* b = components[j];
            if (b->minX > a->maxX)
                break;

            if (a->maxY < b->minY || a->minY > b->maxY)
                continue;

            // collision contact info
            ContactInfo contact;

            if (a->isCollision(b, contact))
            {
                a->currentFrameCollisions[b] = contact;
                // B �� contact�� ������ �ݴ�� �ؼ� ����
                ContactInfo inverseContact = contact;
                inverseContact.normal = { -contact.normal.x, -contact.normal.y };
                b->currentFrameCollisions[a] = inverseContact;
            }
        }
    }

    // Enter / Stay / Exit
    for (auto collider : components)
    {
        collider->FinalizeCollision();
    }
}

// Raycast ������ �ݶ��̴��� �浹 ���� ��ȯ
RaycastHit ColliderSystem::Raycast(const Ray& ray, float maxDistance)
{
    RaycastHit closestHit;
    closestHit.collider = nullptr;
    closestHit.distance = maxDistance;

    for (ICollider* col : components)
    {
        // trigger collider�� ����
        if (col->isTrigger) continue;

        RaycastHit hitInfo;
        if (col->Raycast(ray, maxDistance, hitInfo))
        {
            // �浹 �ݶ��̴��� ���� ����� ������ ����
            if (hitInfo.distance < closestHit.distance)
            {
                closestHit = hitInfo;
            }
        }
    }

    // �浹�� �ݶ��̴� ���� ��� closesHit.collider == nullptr;
    return closestHit;
}