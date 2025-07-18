#include "Camera.h"
#include "Transform.h"
#include "GameObject.h"


void Camera::OnEnable()
{
	transform = this->owner->GetComponent<Transform>();
    if (mainCamera == nullptr) mainCamera = this;
}

void Camera::OnDestroy()
{
	if (mainCamera == this) mainCamera = nullptr;
}

void Camera::Update()
{
    if (!transform) return;

    // matrix udpate
    worldMatrix = transform->GetWorldMatrix();
    inverseMatrix = worldMatrix;
    inverseMatrix.Invert();
}

// static
// main camera
Camera* Camera::mainCamera = nullptr;

void Camera::SetMainCamera(Camera* cam)
{
	mainCamera = cam;
}

Camera* Camera::GetMainCamera()
{
	return mainCamera;
}

const D2D1::Matrix3x2F& Camera::GetMainInverseMatrix()
{
    return mainCamera->inverseMatrix;
}

// Culling
bool Camera::IsInView(const Vector2& worldPos, const Vector2& boundSize) const
{
    if (!transform) return false;

    Vector2 cameraPos = transform->GetPosition();
    Vector2 viewPos = worldPos - cameraPos;

    float halfW = viewWidth * 0.5f;
    float halfH = viewHeight * 0.5f;

    return !(viewPos.x + boundSize.x < -halfW ||
        viewPos.x - boundSize.x >  halfW ||
        viewPos.y + boundSize.y < -halfH ||
        viewPos.y - boundSize.y >  halfH);
}