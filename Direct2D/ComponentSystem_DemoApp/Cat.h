#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h";
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/TextRenderer.h"
#include "../Direct2D_EngineLib/Time.h"

class Cat : public GameObject
{
private:
	float moveSpeed = 100.0f;
	float moveDirection = -1.0f;

public:
	Transform* transform;
	SpriteRenderer* sr;
	TextRenderer* tr;

	// TODO :: ScriptComponent, ScriptSystem
	// 현재는 Scene->SceneManager->GameObject 구조로 호출되는
	// Cycle에 의존하여 이 안에 conponent 제어 로직을 작성하고 있지만
	// 추후 ScriptComponent, ScriptSystem을 생성하여 유니티처럼
	// 게임오브젝트의 Component를 Get해서 각 기능별 제어 로직을 따로 작성할 예정
	// ScriptSystem -> OnEnable, Update, OnDestroy
	// ex) CatController, CatInputSystem 등
	void Awake() override;
	void Start() override;
	void Update() override;
	void Destroy() override;

public:
	void ChangeDirection();
};

