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
	for (auto& object : objectList)
	{
		if (!ObjectTable::Get().IsValid(object)) {
			// »©±â
		}
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
		object->Destroyed();
		delete object;
	}
	objectList.clear();
}