#pragma once
#include <vector>
#include <windows.h> 
#include "GameObject.h"
#include "Object.h"

using namespace std;

/* [Scene 클래스]
* 게임 콘텐츠에서의 Scene의 Base로 각 씬에 GameObect를 등록시켜 GameObject의 Cycle를 호출한다.
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

	// Game Object
	template<typename T, typename... Args>
	T* CreateObject(Args&&... args)
	{
		T* pObject = new T(std::forward<Args>(args)...);
		objectList.push_back(pObject);
		pObject->Awake();			// GameObject->Awake()
		return pObject;
	}

	// Create시 포인터로만 delete 가능함
	// TODO :: GameObject Find로 삭제하는 방법 찾아보기
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

	// 리소스 제거용 test 함수
	void TestCatPop() {
		if (objectList.back()->name == "Cat") {
			objectList.back()->Destroyed();
			delete objectList.back();
			objectList.pop_back();
			return;
		}

		OutputDebugStringA("삭제할 Cat이 없습니다.\n");
	}
};

