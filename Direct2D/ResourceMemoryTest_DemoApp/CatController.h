#pragma once
#include "../Direct2D_EngineLib/Script.h"
#include "../Direct2D_EngineLib/Transform.h";
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/Time.h"

class CatController : public Script
{
private:
	float rotationSpeed = 120.0f;
	float rotationDirection = -1.0f;
	Transform* tr;

public:
	void OnEnable() override;
	void Update() override;
	void OnDestroy() override;
};

