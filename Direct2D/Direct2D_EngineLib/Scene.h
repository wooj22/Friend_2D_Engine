#pragma once
#include <vector>
using namespace std;

/* [Scene 클래스]
* 게임 콘텐츠에서의 Scene의 Base로 각 씬에 GameObect를 등록시켜 GameObject의 Cycle을 호출한다.
* SceneManager -> Scene(this) -> GameObject
*/

class GameObject;
class Scene
{
private:
	vector<GameObject*> objectList;

public:
	Scene() = default;
	virtual ~Scene() { Clear(); }

	// Scene Life Cycle
	virtual void Awake();		// GameObjects->Awake()
	virtual void Start();		// GameObjects->Start()
	virtual void Update();		// GameObjects->Update()
	virtual void Exit();		// GameObjects->Destroy()
	void Clear();

	// Game Object
	template<typename T>
	T* CreateObject()
	{
		T* pObject = new T();
		objectList.push_back(pObject);
		return pObject;
	}

	template<typename T>
	void DeleteObject(T object)
	{
		auto it = find(objectList.begin(), objectList.end(), object);
		objectList.erase(it);
	}
};

