#pragma once
#include <d2d1_1.h>
#include <vector>
#include "Vector2.h"
#include "ITransform.h"
#include "TransformSystem.h"

/* [Transform Component]
* D2D1::MATRIX_3X2_F : 2D ��ȯ(�̵�, ȸ��, ������, ����)�� ǥ���ϴ� 3*2 ���
* �� ����� �̿��Ͽ� ������Ʈ�� ��ȯ�� ����ϴ� ������Ʈ�̴�.
* ������Ʈ ������ Transform System�� ��ϵǾ� dirty���Ͽ� ���� matrix�� ��� ����Ѵ�.

// position ��� ���
* World = local * parent->world
* Screen = world * camera �����

// Uniny Style Screen position
* ��ǥ�� - �߾� (0,0), ������(-, +), ������ �Ʒ�(+, -)
* D2D���� ����Ƽ ��ǥ��ó�� ����Ϸ��� �ļ��� �ʿ���
* Screen = renderMatrix * world * camera ����� * unity matrix
* unity matrix�� �߽� �̵��� y ������ ���� ��İ��� ������ �ִ�.
* renderMatrix�� unity matrix�� �����ϱ� ���� y scale�� -1�� �� ���
* transform ����� �����ϸ� �ڽı��� ���� ������ ��ġ�� ������ ���꿡�� ����ؾ��Ѵ�.

// Dirty ����
* transform�� ���濡 ���� flag�� Ȱ���Ͽ�
* �� �����Ӹ��� ���ʿ��ϰ� ����� �ٽ� ������� �ʵ��� �ϴ� ���
*/

class Transform : public ITransform
{
private:
    // transform
    Vector2 position;
    float rotation;
    Vector2 scale;

public:
    Vector2 prePosition;    // ���� ������ position

private:
    // parent, children
    Transform* parent = nullptr;
    std::vector<Transform*> children;
    
    // this matrix
    D2D1::Matrix3x2F localMatrix;
    D2D1::Matrix3x2F worldMatrix;
    D2D1::Matrix3x2F screenMatrix;

    // dirty
    bool isLocalDirty = true;
    bool isWorldDirty = true;

public:
    // matrix
    static D2D1::Matrix3x2F unityMatrix;          // ����, screen size �ʿ�
    static D2D1::Matrix3x2F renderMatrix;         // ����

public:
    // component cycle
    Transform() : position{ 0.0f, 0.0f }, rotation(0.0f), scale{ 1.0f, 1.0f }, parent(nullptr) 
    {
        localMatrix = D2D1::Matrix3x2F::Identity();
        
    }
    ~Transform() override = default;

    void OnEnable_Inner() override final;
	void OnDisable_Inner() override final;
    void Update() override final;
    void OnDestroy_Inner() override final;

public:
    // parent, children
    void SetParent(Transform* newParent);
	Transform* GetParent(Transform* newParent) { return parent; }
    const vector<Transform*>& GetChildrens() { return children; }
    void RemoveChild(Transform* child);
    void MarkWorldDirty();

    // set
    void SetPosition(const Vector2& position);
    void SetPosition(const float& x, const float& y);
    void SetRotation(const float& angle);
    void SetScale(const Vector2& scale);
    void SetScale(const float& scaleX, const float& scaleY);
    void ResetTransform();

    // add
    void Translate(const Vector2& translation);
    void Translate(const float& x, const float& y);
    void Rotate(const float& angle);
    void Scaleing(const Vector2& scale);
    void Scaleing(const float& scaleX, const float& scaleY);

    // get
    Vector2 GetPosition() const { return position; }
    float GetRotation() const { return rotation; }
    Vector2 GetScale() const { return scale; }

    Vector2 GetWorldPosition() const
    {
        if (parent)
            return parent->GetWorldPosition() + position;
        return position;
    }

    float GetWorldRotation() const
    {
        if (parent)
            return parent->GetWorldRotation() + rotation;
        return rotation;
    }

    Vector2 GetWorldScale() const
    {
        if (parent)
        {
            Vector2 parentScale = parent->GetWorldScale();
            return Vector2(scale.x * parentScale.x, scale.y * parentScale.y);
        }
        return scale;
    }

private:
    //  matrix
    void MakeLocalMatrix();
    void MakeWorldMatrix();
    void MakeScreenMatrix();

public:
    //  matrix get
    const D2D1::Matrix3x2F& GetLocalMatrix() { return localMatrix; }
    const D2D1::Matrix3x2F& GetWorldMatrix(){ return worldMatrix; }
    const D2D1::Matrix3x2F& GetScreenMatrix() { return screenMatrix; }
};