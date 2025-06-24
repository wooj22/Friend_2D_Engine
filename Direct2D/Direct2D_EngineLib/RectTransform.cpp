#include "RectTransform.h"

// component cycle
void RectTransform::OnEnable()
{

}

void RectTransform::OnDestroy()
{

}

void RectTransform::Update()
{
    MakeScreenMatrix();
}

// set
void RectTransform::SetPosition(float x, float y)
{
    position = { x, y };
    isDirty = true;
}

void RectTransform::SetSize(float w, float h)
{
    size = { w, h };
    isDirty = true;
}

void RectTransform::SetPivot(float x, float y)
{
    pivot = { x, y };
    isDirty = true;
}

// Screen Matrix
inline void RectTransform::MakeScreenMatrix()
{
    if (!isDirty) return;

    float offsetX = -size.width * pivot.x;
    float offsetY = -size.height * pivot.y;

    // 화면 고정 좌표 행렬 계산
    screenMatrix =
        D2D1::Matrix3x2F::Translation(offsetX, offsetY) *
        D2D1::Matrix3x2F::Translation(position.x, position.y);

    isDirty = false;
}