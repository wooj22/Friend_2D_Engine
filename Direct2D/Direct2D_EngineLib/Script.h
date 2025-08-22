#pragma once
#include "Component.h"
#include "ScriptSystem.h"
#include "GameObject.h"
#include "ICollider.h"
#include "SceneManager.h"
#include "Scene.h"

/* [Script Conponent]
* GameObject�� ���� Component���� controll�ϴ� script ������Ʈ�̴�.
* ���� ������������ �� class�� ��ӹ��� script�� �ۼ��Ͽ�
* ��ɺ��� ��ũ��Ʈ�� �и��ϰ�, ��Ȱ�� �� �� �ִ�. ex) Movement.cs, Inventory.cs
* -> ����Ƽ�� �������̾��� �����ϸ� �ȴ�.
*/

class ICollider;
class Script : public Component
{
public:
    bool started = false;

    /* script component cycle */
    Script() = default;
	~Script() override = default;

    virtual void OnEnable() {}         // ������Ʈ Ȱ��ȭ��
    virtual void OnDisable() {}        // ������Ʈ ��Ȱ��ȭ��
    virtual void Awake() {}            // Update()���� 1ȸ ȣ��
    virtual void Start() {}            // Awake() ���� Updtae() ���� ���� 1ȸ ȣ��
    virtual void Update() {}           // ������ ���� �ݺ� ȣ��
    virtual void LateUpdate() {}       // Camera ��
    virtual void FixedUpdate() {}      // ���� ������Ʈ 0.02f ���� �ݺ� ȣ��
    virtual void OnDestroy() {}        // ������Ʈ or ������Ʈ �Ҹ� ����
	

    /* activate inner */
    void OnEnable_Inner() override final
    {
        ScriptSystem::Get().Regist(this);
        OnEnable();
    }

    void OnDisable_Inner() override final
    {
        ScriptSystem::Get().Unregist(this);
        OnDisable();
    }

    void OnDestroy_Inner() override final
    {
        ScriptSystem::Get().Unregist(this);
        OnDestroy();
    }


    /* Collition Event */
    // trigger
    virtual void OnTriggerEnter(ICollider* other, const ContactInfo& contact) {}
    virtual void OnTriggerStay(ICollider* other, const ContactInfo& contact) {}
    virtual void OnTriggerExit(ICollider* other, const ContactInfo& contact) {}

    // collision
    virtual void OnCollisionEnter(ICollider* other, const ContactInfo& contact) {}
    virtual void OnCollisionStay(ICollider* other, const ContactInfo& contact) {}
    virtual void OnCollisionExit(ICollider* other, const ContactInfo& contact) {}

    /* Instantiate */
	template<typename T, typename... Args>
	T* Instantiate(Vector2 position = { 0,0 }, GameObject* parent = nullptr, Args&&... args)
	{
		return SceneManager::Get().GetCurrentScene()->CreateObject<T>(position, parent, std::forward<Args>(args)...);
	}
};



