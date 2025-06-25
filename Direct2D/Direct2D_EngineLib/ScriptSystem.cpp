#include "ScriptSystem.h"
#include "Script.h"

// component 등록
void ScriptSystem::Regist(Script* component)
{
	components.push_back(component);
}

// component 등록 해제
void ScriptSystem::Unregist(Script* component)
{
	for (auto it = components.begin(); it != components.end(); ++it) {
		if (*it == component) {
			components.erase(it);
			return;
		}
	}
}

// component system
void ScriptSystem::Update()
{
	for (auto it = components.begin(); it != components.end(); ++it)
	{
		(*it)->Update();
	}
}