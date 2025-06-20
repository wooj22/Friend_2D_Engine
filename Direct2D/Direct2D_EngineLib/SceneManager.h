#pragma once
#include <vector>
#include "Singleton.h"
using namespace std;

/* [SceneManager 클래스]
* 게임 콘텐츠에서 게임 시작시 CreateScene()으로 전체 씬을 SceneManager에 등록시키고,
* 모든 Scene들을 sceneList로 관리하여 현재 씬의 Update를 호출한다.
* SceneManager에서 현재 씬의 Updete를 호출 -> Scene에서 오브젝트들의 update 호출
*/

class Scene;
class SceneManager : public Singleton<SceneManager>
{
private:
	vector<Scene*> sceneList;		   // 씬 리스트
	Scene* currentScene = nullptr;     // 현재 씬
	Scene* nextScene = nullptr;        // 다음 씬

public:
	SceneManager() = default;
	~SceneManager() = default;

	void Init();
	void Update();
	void UnInit();

	template<typename T>
	void CreateScene()
	{
		Scene* pScene = new T();
		sceneList.push_back(pScene);
	}

	void SetCurrentScene(size_t index);
	Scene* GetCurrentScene();
	void ChangeScene(size_t index);
};

