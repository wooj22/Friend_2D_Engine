#include "ColliderSystem.h"
#include <algorithm>
#include "ICollider.h"
#include "BoxCollider.h"
#include "CircleCollider.h"

// component 등록
void ColliderSystem::Regist(ICollider* component)
{
	components.push_back(component);
    OutputDebugStringA("BoxCollider Regist()\n");
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


void ColliderSystem::DebugColliderDraw()
{
    for (auto& col : components)
    {
        col->DebugColliderDraw();
    }
}