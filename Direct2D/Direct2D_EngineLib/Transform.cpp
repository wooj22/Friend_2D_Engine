#include "Transform.h"

// Game App에서 초기화 필요
// 일단 카메라 움직임 없고, (1024, 768) 기준으로 수동 초기화
D2D1::Matrix3x2F Transform::cameraInversMatrix = 
    D2D1::Matrix3x2F::Identity();
D2D1::Matrix3x2F Transform::unityMatrix = 
    D2D1::Matrix3x2F::Scale(1.0f, -1.0f) *
    D2D1::Matrix3x2F::Translation(1024.0f / 2.0f, 768.0f / 2.0f);
D2D1::Matrix3x2F Transform::renderMatrix =
    D2D1::Matrix3x2F::Scale(1.0f, -1.0f);

// SetParent
void Transform::SetParent(Transform* newParent)
{
    parent = newParent;
    if (parent)
        parent->children.push_back(this);
}

// Reset
void Transform::ResetTransform()
{
    position = { 0.0f, 0.0f };
    rotation = { 0.0f };
    scale = { 1.0f, 1.0f };
    isDirty = true;
}

// Local Tansform get
D2D1::Matrix3x2F Transform::GetLocalMatrix()
{
    if (isDirty) {
        localMatrix = D2D1::Matrix3x2F::Scale(scale.x, scale.y) *
            D2D1::Matrix3x2F::Rotation(rotation) *
            D2D1::Matrix3x2F::Translation(position.x, position.y);

        isDirty = false;
    }
    
    return localMatrix;
}

// World Tansform get
// World = Local * ParentWorld;
D2D1::Matrix3x2F Transform::GetWorldMatrix()
{
    auto worldMatrix = GetLocalMatrix();
    worldMatrix = parent ? worldMatrix * parent->GetWorldMatrix() : worldMatrix;
    return worldMatrix;
}

// Screen Tansform get
D2D1::Matrix3x2F Transform::GetScreenMatrix()
{
    //return GetWorldMatrix() * cameraInversMatrix;
    return renderMatrix * GetWorldMatrix() * cameraInversMatrix * unityMatrix;
}