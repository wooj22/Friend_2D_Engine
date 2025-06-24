#pragma once
#include <vector>
#include <typeinfo>
#include "Component.h"

/* [GameObject 클래스]
* Component를 등록시킬 수 있는 오브젝트로,
* 게임 콘텐츠에 활용할 오브젝트는 이 클래스를 상속받아 컴포넌트를 조합하여 구현한다.
* 게임 오브젝트는 Scene에 등록되어 Scene Life Cycle대로 Cycle이 호출된다.
* SceneManager -> Scene -> GameObject(this)
*/

class Component;
class GameObject {
private:
    std::vector<Component*> components;

public:
    GameObject() {};
    virtual ~GameObject()
    {
        for (Component* comp : components) {
            comp->OnDestroy();
            delete comp;
        }
        components.clear();
    }

    // Cycle
    virtual void Awake() {};
    virtual void Start() {};
    virtual void Update() {};
    virtual void Destroy() {};

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