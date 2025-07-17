#include "Scene.h"
#include "GameObject.h"

/// Scene Start
void Scene::Start()
{
	for (auto& object : objectList)
	{
		object->SceneStart();
	}
}

/// Scene Update
void Scene::Update()
{
	// game object update
	for (auto& object : objectList)
	{
		if (!object->IsDestroyed())
			object->Update();
	}

	// destroyed gameobject delete
	auto it = objectList.begin();
	while (it != objectList.end()) 
	{
		GameObject* obj = *it;
		if (obj->IsDestroyed()) {
			obj->Destroyed();
			delete obj;
			it = objectList.erase(it);
		}
		else { ++it; }
	}
}

/// Scene Exit
void Scene::Exit()
{
	Clear();
}

/// Scene GameObject Clear
void Scene::Clear()
{
	for (auto& object : objectList)
	{
		object->Destroyed();
		delete object;
	}
	objectList.clear();
}