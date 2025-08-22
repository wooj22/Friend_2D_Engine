#pragma once
#include <vector>
#include <windows.h> 
#include "GameObject.h"
#include "Object.h"
#include "Transform.h"

using namespace std;

/* [Scene]
* ���ӿ�����Ʈ�� �����̳� ������ �����ϸ� ���� ������Ʈ ����Ŭ�� ȣ���Ѵ�.
* ���� GameObject�� ������ �� : GameObject->Awake()
* ���� Start�� �� : GameObject->SceneStartInit()
* ���� Update�� �� : GameObject->Update()
* ���� GameObject�� ������ų �� : GameObject->Destroyed()
* 
* ���ӿ�����Ʈ�� �����ɶ� �ٷ� objectList�� �߰��ϴ°� �ƴ�, 
* pending_objectList�� �߰��ϰ�, vector�� update�� ���� �� objectList�� �߰��Ѵ�.
* Update�� capacity�� ����� ��� ũ���ø� ������ �� �ִ�.
*/

class GameObject;
class Scene : public Object
{
private:
	vector<GameObject*> objectList;
	vector<GameObject*> pending_objectList;

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
	T* CreateObject(Vector2 position = {0,0}, GameObject* parent = nullptr, Args&&... args)
	{
		// new
		T* pObject = new T(std::forward<Args>(args)...);
		pending_objectList.push_back(pObject);

		// transform, parent
		Transform* tr = pObject->GetComponent<Transform>();
		if (tr)
		{
			tr->SetPosition(position);
			if (parent)
			{
				Transform* parentTr = parent->GetComponent<Transform>();
				if (parentTr)
				{
					tr->SetParent(parentTr);
				}
			}
		}

		// cycle
		pObject->Awake();
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
			OutputDebugStringA("������ GameObject�� �����ϴ�.\n");
		}
	}

	// Set capacity
	void SetObjectListCapacity(size_t capacity);
};

