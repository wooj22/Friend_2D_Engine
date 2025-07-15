#pragma once
#include "../Direct2D_EngineLib/Script.h"
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/ICollider.h"

class Transform;
class SpriteRenderer;
class AnimatorController;
class WorldTextRenderer;
class Rigidbody;

class CatController : public Script
{
private:
	// stat
	float curSpeed = 0;
	float walkSpeed = 5.f;
	float runSpeed = 10.f;
	float jumpForce = 4000.0f;

	// move
	float inputX, inputY;

	// key
	bool isW, isA, isS, isD, isShift, isSpace;

	// ref component
	Transform* tr;
	SpriteRenderer* sr;
	Rigidbody* rb;
	AnimatorController* ac;

public:
	WorldTextRenderer* infoText;

public:
	// script component cycle
	void OnEnable() override;				// 컴포넌트 활성화 시점
	void Awake() override;					// 오브젝트의 모든 컴포넌트가 생성된 직후 시점 1회 호출
	void Start() override;					// Awake() 이후 시점 1회 호출
	void Update() override;					// 매 프레임 반복 호출
	void FixedUpdate() override;			// 물리 업데이트 0.02f 보장 반복 호출
	void OnDestroy() override;				// 컴포넌트 or 오브젝트 소멸 시점

	// trigger
	void OnTriggerEnter(ICollider* other) override { OutputDebugStringA("OnTriggerEnter()\n"); }
	void OnTriggerStay(ICollider* other)  override { OutputDebugStringA("OnTriggerStay()\n"); }
	void OnTriggerExit(ICollider* other)  override { OutputDebugStringA("OnTriggerExit()\n"); }

	// collision
	void OnCollisionEnter(ICollider* other)  override 
	{ 
		if (other->owner->name == "Cloud") {
			OutputDebugStringA("OnCollisionEnter() - Could\n");
		}
	}

	void OnCollisionStay(ICollider* other) override 
	{ 
		if (other->owner->name == "Cloud") {
			OutputDebugStringA("OnCollisionStay() - Could\n");
		}
	}

	void OnCollisionExit(ICollider* other)  override 
	{ 
		if (other->owner->name == "Cloud") {
			OutputDebugStringA("OnCollisionExit() - Could\n");
		}
	}

public:
	float GetSpeed() { return curSpeed; }

private:
	void InputCheak();
	void Move_Transform();
	void Move_Physics();
	void Jump_Physics();
	void InfoTextUpdate();
};

