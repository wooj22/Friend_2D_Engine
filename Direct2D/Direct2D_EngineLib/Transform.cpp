#include "Transform.h"

// static mamber init
D2D1::Matrix3x2F Transform::cameraInversMatrix = D2D1::Matrix3x2F::Identity();
D2D1::Matrix3x2F Transform::unityMatrix = D2D1::Matrix3x2F::Identity();
D2D1::Matrix3x2F Transform::renderMatrix = D2D1::Matrix3x2F::Scale(1.0f, -1.0f);

void Transform::OnEnable()
{
    
}

void Transform::OnDestroy()
{

}

void Transform::Update() 
{
    MakeLocalMatrix();
    MakeWorldMatrix();
}


// Set Parent
void Transform::SetParent(Transform* newParent)
{
    // 부모가 같을 경우
    if (newParent == parent) return;

    // 부모 set
    if (parent != nullptr) {
        parent->RemoveChild(this);
    }

    parent = newParent;
    if (parent)
        parent->children.push_back(this);

    MarkWorldDirty();
}

// Remove Child
void Transform::RemoveChild(Transform* removeChild) 
{
    for (auto it = children.begin(); it != children.end(); ++it)
    {
        if (*it != removeChild)
            continue;

        it = children.erase(it);
        break;
    }
}

// Mark World Dirty
void Transform::MarkWorldDirty() 
{
    isWorldDirty = true;
    for (auto it = children.begin(); it != children.end(); ++it) {
        (*it)->MarkWorldDirty();
    }
}

// set
void Transform::SetPosition(float x, float y) 
{ 
    isLocalDirty = true;
    position = { x, y }; 
    MarkWorldDirty();
}

void Transform::SetRotation(float angle) 
{ 
    isLocalDirty = true; 
    rotation = angle; 
    MarkWorldDirty();
}

void Transform::SetScale(float scaleX, float scaleY) 
{
    isLocalDirty = true; 
    scale = { scaleX, scaleY }; 
    MarkWorldDirty();
}

void Transform::ResetTransform() 
{ 
    position = { 0.0f, 0.0f };
    rotation = { 0.0f }; scale = { 1.0f, 1.0f }; 
    isLocalDirty = true; 
    MarkWorldDirty();
}

// add
void Transform::AddPosition(float x, float y)
{ 
    isLocalDirty = true;
    position.x += x; position.y += y;
    MarkWorldDirty();
}

void Transform::AddRotation(float angle)
{
    isLocalDirty = true;
    rotation += angle; 
    MarkWorldDirty();
}

void Transform::AddScale(float scaleX, float scaleY) 
{ 
    isLocalDirty = true; 
    scale.x += scaleX; scale.y += scaleY; 
    MarkWorldDirty();
}

// Local Matrix
void Transform::MakeLocalMatrix() 
{
    if (isLocalDirty) {
        localMatrix = D2D1::Matrix3x2F::Scale(scale.x, scale.y) *
            D2D1::Matrix3x2F::Rotation(rotation) *
            D2D1::Matrix3x2F::Translation(position.x, position.y);

        isLocalDirty = false;
    }
}

// World Matrix
void Transform::MakeWorldMatrix() {
    if (isWorldDirty) {
        auto worldMatrix = GetLocalMatrix();
        this->worldMatrix = parent ? worldMatrix * parent->GetWorldMatrix() : worldMatrix;

        isWorldDirty = false;
    }
}