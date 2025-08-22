#include "ScriptSystem.h"
#include "Script.h"

// component ���
void ScriptSystem::Regist(Script* component)
{
	pending_components.push_back(component);
}

// component ��� ����
void ScriptSystem::Unregist(Script* component)
{
	// script delete
	for (auto it = components.begin(); it != components.end(); ++it) {
		if (*it == component) {
			components.erase(it);
			return;
		}
	}

	// pending script delete
	for (auto it = pending_components.begin(); it != pending_components.end(); ++it) {
		if (*it == component) {
			pending_components.erase(it);
			return;
		}
	}
}

// update -> ������(deltaTime) ���� ȣ��
void ScriptSystem::Update()
{
	// pending_components push
	for (Script* script : pending_components)
	{
		components.push_back(script);
	}
	pending_components.clear();
	

	// update
	for (Script* script : components)
	{
		// update�� ������ ���
		if (!script->started)
		{
			script->Awake(); 
			script->Start();
			script->started = true;
		}
		script->Update();
	}
}

// LateUpdate -> Update Loop ���� ȣ��
void ScriptSystem::LateUpdate()
{
	// pending_components push
	for (Script* script : pending_components)
	{
		components.push_back(script);
	}
	pending_components.clear();


	// update
	for (Script* script : components)
	{
		script->LateUpdate();
	}
}

// fixed udpate -> deltaTime�� ���� �ʾ����ٸ� ������ ȣ���ϰ� �Ѿ
void ScriptSystem::FixedUpdate()
{
	// pending_components push
	for (Script* script : pending_components)
	{
		components.push_back(script);
	}
	pending_components.clear();

	// fixed udpate
	for (Script* script : components)
	{
		// update�� ������ ���
		if (!script->started)
		{
			script->Awake();
			script->Start();
			script->started = true;
		}

		if (script) script->FixedUpdate();
	}
}