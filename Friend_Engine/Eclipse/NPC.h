#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h"
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/BoxCollider.h"
#include "../Direct2D_EngineLib/Rigidbody.h"
#include "../Direct2D_EngineLib/Animator.h"
#include "NpcAnimatorController.h"
#include "../Direct2D_EngineLib/WorldTextRenderer.h"

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

	// ������Ʈ�� ������ ��
	void Awake() override;

	// Scene�� Start (���� ��� ������Ʈ�� �����ǰ� �� ��)
	void SceneStart() override;

	// Scene�� Update
	void Update()  override;

	// Scene�� Exit, GameObject Delete
	void Destroyed() override;
};