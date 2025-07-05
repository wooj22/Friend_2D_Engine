#include "AnimatorSystem.h"
#include "Animator.h"

// component 등록
void AnimatorSystem::Regist(Animator* component)
{
	components.push_back(component);
}

// component 등록 해제
void AnimatorSystem::Unregist(Animator* component)
{
	for (auto it = components.begin(); it != components.end(); ++it) {
		if (*it == component) {
			components.erase(it);
			return;
		}
	}
}

// component system
void AnimatorSystem::Update()
{
	for (auto it = components.begin(); it != components.end(); ++it)
	{
		(*it)->Update();
	}
}
