#pragma once
#include "../Friend_2D_EngineLib/GameObject.h"
#include "../Friend_2D_EngineLib/Transform.h"
#include "../Friend_2D_EngineLib/SpriteRenderer.h"
#include "../Friend_2D_EngineLib/BoxCollider.h"
#include "../Friend_2D_EngineLib/Rigidbody.h"
#include "../Friend_2D_EngineLib/Animator.h"
#include "NpcAnimatorController.h"
#include "../Friend_2D_EngineLib/WorldTextRenderer.h"

#include "NPCInteraction.h"
#include "PlayUI.h"

class NPC : public GameObject
{
public:
	SpriteRenderer* spriteRenderer;
	Rigidbody* rigidbody;
	BoxCollider* collider;
	Animator* animator;
	NPCInteraction* script;
	GameObject* interactImage;
	GameObject* interactText;

	NpcAnimatorController* animatorController;

public:
	// game object cycle
	NPC();
	~NPC() override {}

	// 오브젝트가 생성될 때
	void Awake() override;

	// Scene의 Start (씬의 모든 오브젝트가 생성되고 난 뒤)
	void SceneStart() override;

	// Scene의 Update
	void Update()  override;

	// Scene의 Exit, GameObject Delete
	void Destroyed() override;
};