#include "ColliderSystem.h"
#include "BoxCollider.h"

// component 등록
void ColliderSystem::Regist(BoxCollider* component)
{
	components.push_back(component);
}

// component 등록 해제
void ColliderSystem::Unregist(BoxCollider* component)
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
	for (auto it = components.begin(); it != components.end(); ++it)
	{
		(*it)->Update();
	}
}
