#pragma once
#include "../Direct2D_EngineLib/Script.h"

class Transform;
class AnimatorController;
class CatController : public Script
{
private:
	Transform* tr;
	AnimatorController* ac;

public:
	void OnEnable() override;
	void Update() override;
	void OnDestroy() override;
};

