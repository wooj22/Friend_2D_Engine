#include "Scene.h"
#include "GameObject.h"

/// Scene Start
void Scene::Start() {
	for (auto& object : objectList)
	{
		object->Start();
	}
}
 
/// Scene Update
void Scene::Update()
{
	for (auto& object : objectList)
	{
		object->Update();
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
		object->Destroy();
		delete object;
	}
	objectList.clear();
}