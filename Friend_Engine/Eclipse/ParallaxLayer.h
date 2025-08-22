#pragma once
#include "../Friend_2D_EngineLib/Script.h"

 /* �� ���� ���� �з����� ��ũ�Ѹ� ������Ʈ */

class Transform;
class Camera;

class ParallaxLayer : public Script
{
public:
	// ���� ��� 0.0(���) ~ 1.0(����)
	float parallaxFactor = 0.2;

private:
	float privousCameraX;
	float currentCameraX;

	// ref
	Transform* tr;
	Transform* maintCameraTr;

public:
	void Awake();
	void Update();
};

