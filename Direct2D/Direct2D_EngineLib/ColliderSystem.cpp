#include "ColliderSystem.h"
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
void ColliderSystem::Update()
{
    // curent frame collision data reset
    for (auto collider : components)
    {
        collider->currentFrameCollisions.clear();
    }

    // collision cheak
	for (size_t i = 0; i < components.size(); ++i)
    {
        for (size_t j = i + 1; j < components.size(); ++j)
        {
            ICollider* a = components[i];
            ICollider* b = components[j];

            if (a->isCollision(b))
            {
                // cur frame collision
                a->currentFrameCollisions.insert(b);
                b->currentFrameCollisions.insert(a);
            }
        }
    }

    // Enter/ Stay/ Exit
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