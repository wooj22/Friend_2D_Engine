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
void RectTransform::SetPosition(const Vector2& position)
{
    this->position = position;
    isDirty = true;
}

void RectTransform::SetPosition(const float& x, const float& y)
{
    position = { x, y };
    isDirty = true;
}

void RectTransform::SetSize(const float& w, const float& h)
{
    size = { w, h };
    isDirty = true;
}

void RectTransform::SetPivot(const float& x, const float& y)
{
    pivot = { x, y };
    isDirty = true;
}

// Screen Matrix
inline void RectTransform::MakeScreenMatrix()
{
    if (!isDirty) return;

    // d2d
    /*float offsetX = -size.width * pivot.x;
    float offsetY = -size.height * pivot.y;*/

    // unity
    float offsetX = -size.width * pivot.x;
    float offsetY = size.height * (1.0f - pivot.y);  // Y 축 반전 고려

    screenMatrix =
        D2D1::Matrix3x2F::Translation(offsetX, offsetY) *     // pivot 보정
        D2D1::Matrix3x2F::Translation(position.x, position.y);

    isDirty = false;
}