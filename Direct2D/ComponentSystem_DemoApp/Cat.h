#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h";
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/WorldTextRenderer.h"
#include "CatController.h"

class Cat : public GameObject
{
public:
	Transform* transform;
	SpriteRenderer* sr;
	WorldTextRenderer* tr;
	CatController* catController;

	// TODO ::
	// 이제 ScriptConponent 만들어서 GameObject cycle 삭제하고
	// 생성자에서 AddComponent 해도 됨
	void Awake() override;
	void Start() override;
	void Update() override;
	void Destroyed() override;
};

