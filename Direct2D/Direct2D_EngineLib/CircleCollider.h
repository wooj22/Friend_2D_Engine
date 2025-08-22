#pragma once
#include "ICollider.h"
#include "ColliderSystem.h"

/* [CircleCollider Component]
* �� �浹 ������ �����Ͽ� �浹 üũ�� ����ϴ� ������Ʈ
* transform�� position�� �������� offset��ŭ ����߸� radius�� �� ������ ������
* bound ������ Update�ϸ� ColliderSystem���� sap �˰����� ����ϵ��� �����Ѵ�.
* ICollider�� ��ӹ��� ��� ������ �ݶ��̴����� ��ȣ�ۿ��� �����Ѵ�.
* isTrigger �÷��׸� �����Ͽ� Block, Overlap ó���� ������ �� �ִ�.
* ColliderSystem�� ��ϵǾ� �浹 �߻��� �浹 �̺�Ʈ�� ȣ���ϰ� �ǰ�,
* �� �̺�Ʈ ������ �°� Script ������Ʈ�� ã�� �̺�Ʈ �Լ��� ȣ�����ش�. -> ����Ƽó�� ��� �����ϵ���
* 
* * Block(collistion mode) ���� ��� - ContectInfo
* �� �ݶ��̴����� �浹 üũ ����� �� �ݶ��̴��� �浹�� ��쿡��
* �浹 ����(point)�� ��������(normal)�� ���� map�� �ݶ��̴��� �Բ� �����Ѵ�.
* FinalizeCollision�������� OnCollision �浹�� ���, �ش� ContectInfo�� �Բ� �����Ͽ� normal�� ���� �̵� �õ��� �����Ѵ�.
*/

class Transform;
class BoxCollider;
class CircleCollider : public ICollider
{
public:
    Transform* transform = nullptr;

    // collider
    Vector2 offset = Vector2::zero;
    float radius = 1.0f;

public:
    // component cycle
    CircleCollider() { colliderType = ColliderType::Circle; }
    ~CircleCollider() override {  }

    void OnEnable_Inner() override final;
    void OnDisable_Inner() override final;
    void OnDestroy_Inner() override final;

private:
    void UpdateBounds() override;
    bool isCollision(ICollider* other, ContactInfo& contact) override;
    void FinalizeCollision() override;

private:
    // collistion cheak
    bool CheckCircleCollision(CircleCollider* other, ContactInfo& contact);
    bool CheckBoxCollision(BoxCollider* other, ContactInfo& contact);

    // raycast hit
    bool Raycast(const Ray& ray, float maxDistance, RaycastHit& hitInfo);

private:
    // collision event
    void OnCollisionEnter(ICollider* other, ContactInfo& contact) override;
    void OnCollisionStay(ICollider* other, ContactInfo& contact) override;
    void OnCollisionExit(ICollider* other, ContactInfo& contact) override;
    void OnTriggerEnter(ICollider* other, ContactInfo& contact) override;
    void OnTriggerStay(ICollider* other, ContactInfo& contact) override;
    void OnTriggerExit(ICollider* other, ContactInfo& contact) override;

public:
    // func
    Vector2 GetCenter() const;
    void DebugColliderDraw() override;
};

