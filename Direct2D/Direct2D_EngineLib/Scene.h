#pragma once
#include <vector>
#include <windows.h> 
#include "GameObject.h"
#include "Object.h"

using namespace std;

/* [Scene]
* 게임오브젝트으 컨테이너 역할을 수행하며 게임 오브젝트 사이클을 호출한다.
* 씬에 GameObject가 생성될 때 : GameObject->Awake()
* 씬이 Start될 때 : GameObject->SceneStartInit()
* 씬이 Update될 때 : GameObject->Update()
* 씬의 GameObject를 삭제시킬 때 : GameObject->Destroyed()
*/

class GameObject;
class Scene : public Object
{
private:
	vector<GameObject*> objectList;

public:
	Scene() = default;
	virtual ~Scene() { Clear(); }

	/* Scene Life Cycle */
	virtual void Awake() = 0;
	virtual void Start();		// GameObjects->SceneStartInit()
	virtual void Update();		// GameObjects->Update()
	virtual void Exit();		// GameObjects->Destroyed()
	void Clear();

	// Create
	template<typename T, typename... Args>
	T* CreateObject(Args&&... args)
	{
		T* pObject = new T(std::forward<Args>(args)...);
		objectList.push_back(pObject);
		pObject->Awake();			// GameObject->Awake()
		return pObject;
	}

	// Delete
	template<typename T>
	void DeleteObject(T object)
	{
		auto it = find(objectList.begin(), objectList.end(), object);
		if (it != objectList.end()) {
			(*it)->Destroyed();;
			delete *it;
			objectList.erase(it);
		}

		else {
			OutputDebugStringA("삭제할 GameObject가 없습니다.\n");
		}
	}
};

