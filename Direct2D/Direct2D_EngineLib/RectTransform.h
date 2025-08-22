#pragma once
#include <d2d1_1.h>
#include "Vector2.h"
#include "ITransform.h"
#include "TransformSystem.h"

/*[RectTransform Componenet]
* UI ���ӿ�����Ʈ ���� Transform ������Ʈ��,  
* ī�޶��� ������ ���� �ʰ� �׻� ������ ȭ�� ��ǥ�� ����Ѵ�.
* ������Ʈ ������ Transform System�� ��ϵǾ� dirty���Ͽ� ���� matrix�� ��� ����Ѵ�.
* 
* RectTranform�� �θ�-�ڽ� ���谡 �����ϸ�
* Position�� �θ��� ������ �ް� size, povot�� ���������� ��ȴ�.
*/

class RectTransform : public ITransform
{
private:
    // rect transform
    Vector2 position = { 0, 0 };
    D2D1_SIZE_F size = { 100, 100 };
    D2D1_POINT_2F pivot = { 0.5f, 0.5f };  // rect�� �߽��� (unity ��ǥ�� ���� left down = 0,0) -> offset ó��

    // parent, children
    RectTransform* parent = nullptr;
    std::vector<RectTransform*> children;

    // this matrix
    D2D1::Matrix3x2F screenLocalMatrix;
    D2D1::Matrix3x2F screenWolrdMatrix;
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
    RectTransform() = default;
    ~RectTransform() override = default;

    void OnEnable_Inner() override final;
	void OnDisable_Inner() override final;
    void Update() override final;
    void OnDestroy_Inner() override final;

public:
    // parent, children
    void SetParent(RectTransform* newParent);
    RectTransform* GetParent() { return parent; }
    const vector<RectTransform*>& GetChildrens() { return children; }
    void RemoveChild(RectTransform* child);
    void MarkWorldDirty();

    // set
    void SetPosition(const Vector2& position);
    void SetPosition(const float& x, const float& y);
    void SetSize(const float& w, const float& h);
    void SetPivot(const float& x, const float& y);

    // get
    D2D1_SIZE_F GetSize() const { return size; }
    Vector2 GetPosition() const { return position; }
    D2D1_POINT_2F GetPivot() const { return pivot; }
    Vector2 GetWorldPosition() const 
    { 
        if (parent)
            return parent->GetWorldPosition() + position;
        return position;
    }

    
private:
    // matrix
    void MakeScreenLocalMatrix();
	void MakeScreenWorldMatrix();

public:
    // parent none pivot matrix get
    const D2D1::Matrix3x2F GetScreenLocalMatrix_NonePivot();
    const D2D1::Matrix3x2F GetScreenWolrdMatrix_NonePivot();

    //  matrix get
	const D2D1::Matrix3x2F& GetScreenLocalMatrix() { return screenLocalMatrix; }
	const D2D1::Matrix3x2F& GetScreenWorldMatrix() { return screenWolrdMatrix; }
	const D2D1::Matrix3x2F& GetScreenMatrix() { return screenMatrix; }
};