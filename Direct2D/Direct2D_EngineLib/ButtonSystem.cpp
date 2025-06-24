#include "ButtonSystem.h"
#include "Button.h"

// component 등록
void ButtonSystem::Regist(Button* component)
{
	components.push_back(component);
}

// component 등록 해제
void ButtonSystem::Unregist(Button* component)
{
	for (auto it = components.begin(); it != components.end(); ++it) {
		if (*it == component) {
			components.erase(it);
			return;
		}
	}
}

// component system
void ButtonSystem::Update()
{
	for (auto it = components.begin(); it != components.end(); ++it)
	{
		(*it)->Update();
	}
}