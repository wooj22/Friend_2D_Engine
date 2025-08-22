#pragma once
#include "../Friend_2D_EngineLib/GameObject.h"
#include "../Friend_2D_EngineLib/Transform.h"
#include "../Friend_2D_EngineLib/SpriteRenderer.h"
#include "../Friend_2D_EngineLib/Animator.h"
#include "../Friend_2D_EngineLib/Time.h"
#include "../Friend_2D_EngineLib/BoxCollider.h"
#include "../Friend_2D_EngineLib/CircleCollider.h"
#include "../Friend_2D_EngineLib/Rigidbody.h"
#include "../Friend_2D_EngineLib/Scene.h"
#include "../Friend_2D_EngineLib/AudioSource.h"
#include "../Friend_2D_EngineLib/AudioClip.h"
#include "../Friend_2D_EngineLib/ResourceManager.h"

#include "PlayerFSM.h"
#include "PlayerAnimatorController.h"

#include "AfterImage.h"
#include "Shadow.h"
#include "PlayerLandingEffect.h"
#include "PlayerAttackArea.h"
#include "PlayerJumpEffect.h"



class Player : public GameObject
{
	Ray ray;
	RaycastHit hit;

public:
	
	// [ components ]
	Transform* transform;
	SpriteRenderer* spriteRenderer;
	Rigidbody* rigidbody;
	BoxCollider* collider;
	Animator* animator;
	AudioSource* audioSource;

	// [ animation asset ]
	PlayerAnimatorController* playerAnimatorController;

	// [ script ]
	PlayerFSM* playerFSM;

	// [ player setting ]
	float playerGravityScale = 100;


	// ------------------------

	// [ playerAttack_Parent ]
	GameObject* playerAttack_Parent = nullptr; 
	Transform* playerAttack_Parent_transform = nullptr; 

	// [ playerAttack ] Attack ����Ʈ & �ݶ��̴� ����
	PlayerAttackArea* playerAttackArea = nullptr;

	// -----------------------

	// [ Shadow ]
	GameObject* player_Shadow = nullptr; // �׸��� ������Ʈ
	Transform* shadow_transform = nullptr;
	SpriteRenderer* shadow_spriteRenderer = nullptr;

	// [ BlackOut ] 
	GameObject* blackOut = nullptr;
	Transform* blackOut_transform = nullptr;
	SpriteRenderer* blackOut_spriteRenderer = nullptr;

	// [ Landing ] 
	PlayerLandingEffect* playerLandingEffect = nullptr;

	// [ Jump ]
	PlayerJumpEffect* playerJumpEffect = nullptr;


public:
	float GetPlayerGravityScale() const { return playerGravityScale; }


public:
	Player() : GameObject("Player", "Player")
	{
		// [ Player ]
		transform = AddComponent<Transform>();
		spriteRenderer = AddComponent<SpriteRenderer>();
		rigidbody = AddComponent<Rigidbody>();
		collider = AddComponent<BoxCollider>();
		animator = AddComponent<Animator>();
		audioSource = AddComponent<AudioSource>();

		spriteRenderer->layer = 25;
		rigidbody->collisionDetection = CollisionDetection::Continuous;

		playerFSM = AddComponent<PlayerFSM>();
		playerFSM->ResetInputs(); // �÷��̾� ���� ��, �Է°� �ʱ�ȭ 


		// [ playerAttack_Parent ]
		playerAttack_Parent = SceneManager::Get().GetCurrentScene()->CreateObject<GameObject>();
		playerAttack_Parent_transform = playerAttack_Parent->AddComponent<Transform>();


		// [ playerAttack ] Attack ����Ʈ & �ݶ��̴� ���� 
		playerAttackArea = SceneManager::Get().GetCurrentScene()->CreateObject<PlayerAttackArea>();

		// ------------- 

		// [ Shadow ] 
		player_Shadow = SceneManager::Get().GetCurrentScene()->CreateObject<Shadow>();

		// [ BlackOut ]
		blackOut = SceneManager::Get().GetCurrentScene()->CreateObject<GameObject>();
		blackOut->name = "BlackOut";
		blackOut->tag = "BlackOut";
		blackOut_transform = blackOut->AddComponent<Transform>();
		blackOut_spriteRenderer = blackOut->AddComponent<SpriteRenderer>();

		// [ Landing Effect ]
		playerLandingEffect = SceneManager::Get().GetCurrentScene()->CreateObject<PlayerLandingEffect>();

		// [ Jump Effect ]
		playerJumpEffect = SceneManager::Get().GetCurrentScene()->CreateObject<PlayerJumpEffect>();

		// [ Audio ]
		audioSource->SetChannelGroup(AudioSystem::Get().GetSFXGroup());

	}
	~Player() override
	{
		delete playerAnimatorController;
	};

	void Awake() override 
	{
		// [ ĳ���� �ִϸ��̼� �ʱ�ȭ ]
		playerAnimatorController = new PlayerAnimatorController();
		animator->SetController(playerAnimatorController);

		// [ Player ]
		transform->SetPosition(-20, -785);
		transform->SetScale(0.5, 0.5);

		collider->offset = { 10.0f, -55.0f };
		collider->size = { 140.0f, 350.0f };

		rigidbody->useGravity = true;
		rigidbody->gravityScale = playerFSM->defaultGravity;
		rigidbody->mass = 1.4f; 


		// [ playerAttack_Parent ]
		playerAttack_Parent_transform->SetParent(transform);
		playerFSM->SetPlayerAttackParent(playerAttack_Parent); // �÷��̾� FSM�� ����

		// [ playerAttackArea ] 
		// playerAttackArea->GetComponent<Transform>()->SetParent(playerAttack_Parent_transform);
		playerFSM->SetPlayerAttackArea(playerAttackArea); // �÷��̾� FSM�� ����

		// -----------------

		// [ �׸��� ]
		shadow_transform = player_Shadow->GetComponent<Transform>();
		shadow_spriteRenderer = player_Shadow->GetComponent<SpriteRenderer>();

		// [ BlackOut ]
		blackOut_spriteRenderer->sprite
			= ResourceManager::Get().CreateSprite(ResourceManager::Get().CreateTexture2D("../Resource/Moon/BlackOut.png"), "BlackOut");
		blackOut_spriteRenderer->layer = 20;
		blackOut_spriteRenderer->SetAlpha(0.5f);
		blackOut_spriteRenderer->SetEnabled(false);

		// [ Landing Effect ]
		// playerLandingEffect->transform->SetParent(transform);

		// [ Jump Effect ]
		// playerJumpEffect->transform->SetParent(transform);
	}


	void Update() override
	{
		UpdateShadow();

		// AABB ���� 
		// collider->DebugColliderDraw();

		//std::string debugStr = "[Player] position = ( " + std::to_string(transform->GetPosition().x) + " , " + std::to_string(transform->GetPosition().y) + " ) \n";
		//OutputDebugStringA(debugStr.c_str());
	}

	void UpdateShadow()
	{
		if (!shadow_transform || !shadow_spriteRenderer)
		{ OutputDebugStringA("[Player] player_Shadow�� Component�� �����ϴ�. \n"); return; }

		// ray 
		ray.direction = Vector2::down;
		ray.origin = transform->GetWorldPosition() - Vector2(0, 120);
		hit = ColliderSystem::Get().Raycast(ray, 5000);

		if (!hit.collider || 
			hit.collider->gameObject->name == "Player" || 
			hit.collider->gameObject->name == "Wall" ||
			hit.collider->gameObject->tag == "BoxObject")
		{
			player_Shadow->GetComponent<SpriteRenderer>()->SetEnabled(false);
			return;
		}

		float distance = transform->GetWorldPosition().y - hit.point.y;
		float maxDistance = 300.0f;

		if (distance > maxDistance)
		{
			player_Shadow->GetComponent<SpriteRenderer>()->SetEnabled(false);
			return;
		}

		if (!player_Shadow->GetComponent<SpriteRenderer>()->IsEnabled())
			player_Shadow->GetComponent<SpriteRenderer>()->SetEnabled(true);

		float alpha = 1.0f - (distance / maxDistance);
		alpha = clamp(alpha, 0.0f, 1.0f);

		if(spriteRenderer->flipX)  player_Shadow->GetComponent<Transform>()->SetPosition({ transform->GetWorldPosition().x - 15.0f , hit.point.y - 7.0f });
		else player_Shadow->GetComponent<Transform>()->SetPosition({ transform->GetWorldPosition().x + 15.0f , hit.point.y - 7.0f });

		player_Shadow->GetComponent<SpriteRenderer>()->SetAlpha(alpha);
	}
};