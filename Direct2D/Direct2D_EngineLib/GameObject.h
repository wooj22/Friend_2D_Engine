#pragma once
#include <vector>
#include <typeinfo>
#include <iostream>
#include <windows.h> 
#include "Component.h"
#include "Object.h"

/* [GameObject 클래스]
* Component를 등록시킬 수 있는 오브젝트로,
* 게임 콘텐츠에 활용할 오브젝트는 이 클래스를 상속받아 컴포넌트를 조합하여 구현한다.
* 게임 오브젝트는 Scene에 등록되어 Scene Life Cycle대로 Cycle이 호출된다.
* SceneManager -> Scene -> GameObject(this)
*/

class Component;
class GameObject : public Object
{
private:
    std::vector<Component*> components;
    static std::vector<GameObject*> allGameObjects;
public:
    std::string name = "GameObject";

public:
    GameObject(const std::string& objName = "GameObject")
        : name(objName)
    {
        allGameObjects.push_back(this);
        OutputDebugStringA("GameObject()\n");
    }

    virtual ~GameObject()
    {
        // component delete
        for (Component* comp : components) {
            comp->OnDestroy();
            delete comp;
        }
        components.clear();

		// gameobject delete
        auto it = std::find(allGameObjects.begin(), allGameObjects.end(), this);
        if (it != allGameObjects.end())
            allGameObjects.erase(it);

        OutputDebugStringA("~GameObject()\n");
    }

public:
    // scene -> gameObject cycle
    virtual void Awake() {};
    virtual void Start() {};
    virtual void Update() {};
    virtual void Destroyed() {};

public:
    // game object find
    static GameObject* Find(const std::string& targetName)
    {
        for (GameObject* obj : allGameObjects)
        {
            if (obj && obj->name == targetName)
                return obj;
        }
        return nullptr;
    }

public:
    // Component
    template<typename T, typename... Args>
    T* AddComponent(Args&&... args)
    {
        static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

        T* comp = new T(std::forward<Args>(args)...);
        comp->owner = this;
        components.push_back(comp);
        comp->OnEnable();
        return comp;
    }

    template<typename T>
    std::vector<T*> GetComponents() {
        std::vector<T*> result;
        for (Component* comp : components) {
            if (auto casted = dynamic_cast<T*>(comp))
                result.push_back(casted);
        }
        return result;
    }

    template<typename T>
    T* GetComponent() {
        for (Component* comp : components) {
            if (typeid(*comp) == typeid(T))
                return static_cast<T*>(comp);
        }
        return nullptr;
    }

    template<typename T>
    bool RemoveComponent(T* target) {

        for (auto it = components.begin(); it != components.end(); ++it) {
            if (*it == target)
            {
                (*it)->OnDestroy();
                delete* it;
                components.erase(it);
                return true;
            }
        }
        return false;
    }
};