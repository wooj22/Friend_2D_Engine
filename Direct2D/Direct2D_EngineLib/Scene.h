#pragma once
#include <vector>
using namespace std;

class GameObject;
class Scene
{
private:
	vector<GameObject*> objectList;

public:
	Scene() = default;
	virtual ~Scene() { Clear(); }

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

	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void Exit();
	void Clear();
};

