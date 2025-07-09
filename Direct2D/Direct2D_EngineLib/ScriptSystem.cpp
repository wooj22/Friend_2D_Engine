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
// 게임 오브젝트에 모든 컴포넌트 생성 후
void ScriptSystem::Awake()
{
	for (Script* script : components)
	{
		script->Awake();
	}
}

// Awake()이후, 첫 Update 전에
void ScriptSystem::Start()
{
	for (Script* script : components)
	{
		script->Start();
		script->started = true;
	}
}

// update -> 프레임(deltaTime) 단위 호출
void ScriptSystem::Update()
{
	for (Script* script : components)
	{
		// update중 생성된 경우
		if (!script->started)
		{
			script->Awake(); 
			script->Start();
		}
		script->Update();
	}
}

// fixed udpate -> deltaTime에 따라 늦어졌다면 여러번 호출하고 넘어감
void ScriptSystem::FixedUpdate()
{
	for (auto* component : components)
	{
		if (component) component->FixedUpdate();
	}
}