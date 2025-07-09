#pragma once
#include <d2d1_1.h>
#include "Vector2.h"
#include "ITransform.h"
#include "TransformSystem.h"

/*[RectTransform Componenet]
* UI 게임오브젝트 전용 Transform 컴포넌트로,  
* 카메라의 영향을 받지 않고 항상 고정된 화면 좌표로 계산한다.
* 컴포넌트 생성시 Transform System에 등록되어 dirty패턴에 따라 matrix를 계속 계산한다.
* 일단 부모 참조 관계는 안만들었다.
*/

class RectTransform : public ITransform
{
private:
    // rect transform
    Vector2 position = { 0, 0 };
    D2D1_SIZE_F size = { 100, 100 };
    D2D1_POINT_2F pivot = { 0.5f, 0.5f };  // rect의 중심점 (unity 좌표계 사용시 left down = 0,0) -> offset 처리

    // this matrix
    D2D1::Matrix3x2F screenMatrix;
    bool isDirty = true;

public:
    // matrix
    static D2D1::Matrix3x2F unityMatrix;          // 고정, screen size 필요
    static D2D1::Matrix3x2F renderMatrix;         // 고정

public:
    // component cycle
    RectTransform() 
    { 
        TransformSystem::Get().Regist(this); 
        OutputDebugStringA("RectTransform()\n");
    }
    ~RectTransform() override 
    { 
        TransformSystem::Get().Unregist(this); 
        OutputDebugStringA("~RectTransform()\n");
    }

    void OnEnable() override;
    void Update() override;
    void OnDestroy() override;

public:
    // set
    void SetPosition(const Vector2& position);
    void SetPosition(const float& x, const float& y);
    void SetSize(const float& w, const float& h);
    void SetPivot(const float& x, const float& y);

    // get
    D2D1_SIZE_F GetSize() const { return size; }
    Vector2 GetPosition() const { return position; }
    D2D1_POINT_2F GetPivot() const { return pivot; }

    
private:
    // matrix
    void MakeScreenMatrix();

public:
    //  matrix get
    const D2D1::Matrix3x2F& GetScreenMatrix() const 
    { 
        // d2d
        //return screenMatrix;

        // unity
        return renderMatrix * screenMatrix * unityMatrix;
    }
};
