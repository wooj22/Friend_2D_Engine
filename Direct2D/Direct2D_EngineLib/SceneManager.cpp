#include "SceneManager.h"
#include "Scene.h"

/// first Scene Init
void SceneManager::Init()
{
	if (currentScene)
		currentScene->Start();
}

/// current Scene Update (scene start, update, exit)
void SceneManager::Update()
{
	if (nextScene)
	{
		if (currentScene)
			currentScene->Exit();

		currentScene = nextScene;
		nextScene = nullptr;

		currentScene->Start();
	}

	if (currentScene)
		currentScene->Update();
}

/// manager Release
void SceneManager::UnInit()
{
	for (auto& scene : sceneList)
	{
		delete scene;
	}
	sceneList.clear();
}

/// current Scene Set (게임 시작 전 set)
void SceneManager::SetCurrentScene(size_t index) {
	if (index >= sceneList.size())
		return;

	currentScene = sceneList[index];
}

/// current Scene get
Scene* SceneManager::GetCurrentScene() {
	return currentScene;
}

/// scene Change
void SceneManager::ChangeScene(size_t index)
{
	if (index >= sceneList.size())
		return;

	nextScene = sceneList[index];
}