#pragma once
#include "Component.h"
#include "CameraSystem.h"

/* [Camera Conponent]
* 
*/

class Transform;
class Camera : public Component
{
private:
	Transform* transform = nullptr;

public:
	// component cycle
	Camera() { CameraSystem::Get().Regist(this); }
	~Camera() override { CameraSystem::Get().Unregist(this); }
	void OnEnable();
	void OnDestroy();
	void Update();
};

