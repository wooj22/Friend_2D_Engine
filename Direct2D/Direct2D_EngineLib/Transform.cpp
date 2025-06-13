#include "Transform.h"

D2D1_MATRIX_3X2_F Transform::cameraInversMatrix = D2D1::Matrix3x2F::Identity();
D2D1_MATRIX_3X2_F Transform::unityMatrix = D2D1::Matrix3x2F::Identity();
D2D1_MATRIX_3X2_F Transform::renderMatrix = D2D1::Matrix3x2F::Scale(0, -1.0f);

// SetParent
void Transform::SetParent(Transform* newParent)
{
    parent = newParent;
    if (parent)
        parent->children.push_back(this);
}

// Local Tansform get
D2D1_MATRIX_3X2_F Transform::GetLocalMatrix() const
{
    return D2D1::Matrix3x2F::Scale(scale.x, scale.y) *
        D2D1::Matrix3x2F::Rotation(rotation) *
        D2D1::Matrix3x2F::Translation(position.x, position.y);
}

// World Tansform get
D2D1_MATRIX_3X2_F Transform::GetWorldMatrix() const
{
    if (parent)
        return parent->GetWorldMatrix() * GetLocalMatrix();
    else
        return GetLocalMatrix();
}