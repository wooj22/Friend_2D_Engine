#include "ColliderSystem.h"
#include <algorithm>
#include "ICollider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

// component 등록
void ColliderSystem::Regist(ICollider* component)
{
	components.push_back(component);
}

// component 등록 해제
void ColliderSystem::Unregist(ICollider* component)
{
	for (auto it = components.begin(); it != components.end(); ++it) {
		if (*it == component) {
			components.erase(it);
			return;
		}
	}
}

// component system
void ColliderSystem::FixedUpdate()
{
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
                b->currentFrameCollisions[a] = contact;
            }
        }
    }

    // Enter / Stay / Exit
    for (auto collider : components)
    {
        collider->FinalizeCollision();
    }
}

// Raycast 광선과 콜라이더의 충돌 정보 반환
RaycastHit ColliderSystem::Raycast(const Ray& ray, float maxDistance)
{
    // ray hit
    for (ICollider* col : components)
    {
        RaycastHit hitInfo;
        if (col->Raycast(ray, maxDistance, hitInfo))
        {
            if (hitInfo.distance <= maxDistance)
                return hitInfo;
        }
    }

    // ray none hit
    RaycastHit closestHit;
    closestHit.collider = nullptr;
    closestHit.distance = maxDistance;
    return closestHit;
}