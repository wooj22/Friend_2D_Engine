#pragma once
#include <vector>
#include <windows.h> 
#include "GameObject.h"
#include "Object.h"

using namespace std;

/* [Scene 클래스]
* 게임 콘텐츠에서의 Scene의 Base로 각 씬에 GameObect를 등록시켜 GameObject의 Cycle을 호출한다.
* SceneManager -> Scene(this) -> GameObject
*/

class GameObject;
class Scene : public Object
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
	virtual void Exit();		// GameObjects->Destroyed()
	void Clear();

	// Game Object
	template<typename T, typename... Args>
	T* CreateObject(Args&&... args)
	{
		T* pObject = new T(std::forward<Args>(args)...);
		objectList.push_back(pObject);
		return pObject;
	}

	// Create시 포인터로만 delete 가능함
	// TODO :: GameObject Find로 삭제하는 방법 찾아보기
	template<typename T>
	void DeleteObject(T object)
	{
		auto it = find(objectList.begin(), objectList.end(), object);
		if (it != objectList.end()) {
			objectList.erase(it);
			return;
		}
		else {
			OutputDebugStringA("삭제할 GameObject가 없습니다.\n");
			return;
		}
	}

	// 리소스 제거용 test 함수
	void TestCatPop() {
		if (objectList.back()->name == "Cat") {
			objectList.back()->Destroyed();
			delete objectList.back();
			objectList.pop_back();
		}

		OutputDebugStringA("삭제할 Cat이 없습니다.\n");
	}
};

