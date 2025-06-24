#include "RectTransform.h"

// static mamber init
D2D1::Matrix3x2F RectTransform::unityMatrix = D2D1::Matrix3x2F::Identity();
D2D1::Matrix3x2F RectTransform::renderMatrix = D2D1::Matrix3x2F::Scale(1.0f, -1.0f);

// component cycle
void RectTransform::OnEnable()
{

}

void RectTransform::Update()
{
    MakeScreenMatrix();
}

void RectTransform::OnDestroy()
{

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

    screenMatrix =
        D2D1::Matrix3x2F::Translation(offsetX, offsetY) *     // pivot º¸Á¤
        D2D1::Matrix3x2F::Translation(position.x, position.y);

    isDirty = false;
}