#include "Camera.h"
#include "Transform.h"
#include "GameObject.h"

void Camera::OnEnable()
{
	transform = this->owner->GetComponent<Transform>();
}

void Camera::OnDestroy()
{
	
}

void Camera::Update()
{
	// TODO
}