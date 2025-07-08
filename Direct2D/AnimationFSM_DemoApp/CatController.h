#pragma once
#include "../Direct2D_EngineLib/Script.h"

class Transform;
class SpriteRenderer;
class AnimatorController;

class CatController : public Script
{
private:
	// stat
	float curSpeed = 0;
	float walkSpeed = 100.f;
	float runSpeed = 300.f;

	// key
	bool isW;
	bool isA;
	bool isS;
	bool isD;
	bool isShift;

	// ref component
	Transform* tr;
	SpriteRenderer* sr;
	AnimatorController* ac;

public:
	// component cycle
	void OnEnable() override;
	void Update() override;
	void OnDestroy() override;

public:
	float GetSpeed() { return curSpeed; }

private:
	void InputCheak();
	void Walk();
	void Run();
};

