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
* 게임 오브젝트는 Scene에 등록되어 Scene의 Update에 따라 Update가 실행된다.
* 
* < GameObject Cycle >
* １．　게임오브젝트 생성자() : 컴포넌트 생성해줘야됨
* ２．　게임오브젝트 ComponentInit()－＞ 컴포넌트 OnEnable()
* ３．　게임오브젝트 Awake()
* ４．　게임오브젝트 SceneStartInit()　// 초기 오브젝트만　해당 (Scene Start() 시점에 생성되어있는 오브젝트)
* ５．　게임오브젝트 Update()
* ６．　게임오브젝트 Destroyed()
* 
* < 콘텐츠 제작시 유의사항 >
* 1) '생성자()'에서 컴포넌트 생성하기
* 2) 오브젝트가 생성되고 가장 먼저  'ComponentInit()'이 호출되어 컴포넌트의 OnEnable()이 실행된다.
*    AddComponent()시에 OnEnable()을 했을 경우 아직 생성되지 않은 컴포넌트를 GetComponent하지 못하는 문제가 해결됨
*    이로써, AddComponent 순서 상관 없이 OnEnable()에서 GetCompoent를 자유롭게 사용해도 됨
* 3) 오브젝트가 생성될 때 ComponentInit()에 이어 'Awake()'가 호출된다. 이때 본인 컴포넌트끼리의 초기화를 마치길 권장한다. 
* 4) Scene이 Start()될 때 'SceneStartInit()'가 호출된다. 
     이때는 씬의 모든 게임오브젝트들이 생성되어있는 시점이므로 Find, 부모관계 지정 등의 작업이 가능하다
     ⭐ 만약 Scene의 Update중간에 생성되는 게임오브젝트라면 SceneStartInit()가 호출되지 않으므로
        SceneStartInit()안에 코드를 작성하지 않아야 한다.
        중간에 생성되는 오브젝트는 다른 게임오브젝트들이 이미 생성된 시점이기 때문에
        생성자나 Awake()에 초기화 코드를 모두 작성하면 된다.
  5) Scene이 Update될 때 'Update()'가 매 프레임 호출된다.
  6) 게임오브젝트가 파괴되거나 씬이 종료될 때 Destroyed()가 호출된다.
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
    /* GameObject Cycle */
    void ComponentInit()             
    {
        // 오브젝트가 생성될 때 Awake()보다 먼저 실행됨
        // 생성자에서 모든 컴포넌트가 생성된 이후 호출되기 때문에 순차 생성에 의한 참조 위험이 없음
        for (Component* comp : components)
            comp->OnEnable();           
    }
    virtual void Awake() = 0;           // 오브젝트가 생성될 때
    virtual void SceneStartInit() = 0;  // Scene의 Start
    virtual void Update() = 0;          // Scene의 Update
    virtual void Destroyed() = 0;       // Scene의 Exit, GameObject Delete

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
        //comp->OnEnable();
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