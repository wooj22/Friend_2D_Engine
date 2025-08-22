#include "PlayerFSM.h"
#include "../Direct2D_EngineLib/Transform.h"
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/AnimatorController.h"
#include "../Direct2D_EngineLib/Animator.h"
#include "../Direct2D_EngineLib/Input.h"
#include "../Direct2D_EngineLib/Time.h"
#include "../Direct2D_EngineLib/WorldTextRenderer.h"
#include "../Direct2D_EngineLib/Rigidbody.h"
#include "../Direct2D_EngineLib/Camera.h"
#include "../Direct2D_EngineLib/RaycastHit.h"
#include "../Direct2D_EngineLib/ColliderSystem.h"

#include "PlayerAnimatorController.h"
#include "Dash_State.h"

#include "GameManager.h"
#include "PlayUI.h"
#include "Chat.h"
#include "HonController.h"
#include "SkillAnimatorController.h"
#include "PlayerSkillEffcet.h"
#include "LandingAnimatorController.h"
#include "HonController.h"



// ������Ʈ Ȱ��ȭ ����
void PlayerFSM::OnEnable()
{

}

void PlayerFSM::Awake()
{
	transform = gameObject->GetComponent<Transform>();
	spriteRenderer = gameObject->GetComponent<SpriteRenderer>();
	rigidbody = gameObject->GetComponent<Rigidbody>();
	animatorController = gameObject->GetComponent<Animator>()->controller;
	audioSource = gameObject->GetComponent<AudioSource>();
	playerAnimatorController = dynamic_cast<PlayerAnimatorController*>(animatorController);
	landingAnimatorController = dynamic_cast<LandingAnimatorController*>(animatorController);

	// [ AudioClip ] 
	SFX_Player_Move1 = ResourceManager::Get().CreateAudioClip("../Resource/Audio/Moon/Player_Footstep1.wav");
	SFX_Player_Move2 = ResourceManager::Get().CreateAudioClip("../Resource/Audio/Moon/Player_Footstep2.wav");
	SFX_Player_Move3 = ResourceManager::Get().CreateAudioClip("../Resource/Audio/Moon/Player_Footstep3.wav");
	SFX_Player_Move4 = ResourceManager::Get().CreateAudioClip("../Resource/Audio/Moon/Player_Footstep4.wav");
	SFX_Player_Jump = ResourceManager::Get().CreateAudioClip("../Resource/Audio/Moon/Player_Jump.wav");
	SFX_Player_Land = ResourceManager::Get().CreateAudioClip("../Resource/Audio/Moon/Player_Rending.wav");
	SFX_Player_Attack = ResourceManager::Get().CreateAudioClip("../Resource/Audio/Moon/Player_Attack.wav");
	SFX_Player_Dash = ResourceManager::Get().CreateAudioClip("../Resource/Audio/Moon/Player_Dash.wav");
	SFX_Player_Q = ResourceManager::Get().CreateAudioClip("../Resource/Audio/Moon/Player_Q.wav");
	SFX_Player_E = ResourceManager::Get().CreateAudioClip("../Resource/Audio/Moon/Player_E.wav");

	// [ FSM �ʱ�ȭ ]
	movementFSM = std::make_unique<MovementFSM>();
	movementFSM->Init(this);
}

void PlayerFSM::Start()
{
	// [ ��ų �ر� ] �׽�Ʈ ���ؼ� 
	// GameManager::Get().AllSkillUnlock();
}

void PlayerFSM::Update()
{
	float dt = Time::GetDeltaTime();

	if (spawnDelay > 0.0f) 
	{
		spawnDelay -= Time::GetDeltaTime();
		ResetInputs(); // �Է� �ʱ�ȭ
		rigidbody->velocity = Vector2(0, 0);
		return;
	}

	movementFSM->Update();

	InputSetting(); // input Ű�� Ȯ��

	// [ ��Ÿ�� ���� ]
	UpdateSkillCooldowns();  
	UpdateDashCooldown(); 

	if (isQ) { TryUseAbsorb(); }
	if (isE) { TryUseRelease(); }
	if (isF) { GameManager::Get().g_playUI->PlayerInteraction(); }

	MouseWorldPos = Camera::GetScreenToWorldPosition(Input::GetMouseScreenPosition());

	SpeedSetting(); // [ Speed Setting ]

	FlipXSetting(); // [ FlipX Setting - ���� �̵� ���� ���� ]

	
	if (isAbsorbSkillActive) 
	{
		AttractionTargetHon(); // [ Q ��ų ���� ]: Ÿ�� ȥ�� �÷��̾� ������ �۾����鼭 �ٰ�����
		
		if(!playerAnimatorController->GetSkillAvailable()) playerAnimatorController->SetSkillAvailable(true);
	} 

	if (isSpeedDown)
	{
		speedDownTimer -= Time::GetDeltaTime();
		if (speedDownTimer <= 0.0f)
		{
			speedDownRate = 1.0f; // ���� �ӵ��� ����
			isSpeedDown = false;

			OutputDebugStringA("[PlayerFSM] �ӵ� ���� ����\n");
		}
	}
	
	// ���� Ÿ�̸� ������Ʈ
	if (speedDownColorTimer > 0.0f)
	{
		speedDownColorTimer -= dt;
		if (speedDownColorTimer <= 0.0f)
		{
			// ���� �������
			spriteRenderer->renderMode = RenderMode::Unlit;
			spriteRenderer->SetBrightness(1.0f);
			OutputDebugStringA("[PlayerFSM] �ӵ� ���� ���� ����\n");
		}
	}

	if (landingSound)
	{
		audioSource->SetClip(SFX_Player_Land);
		audioSource->PlayOneShot();
		landingSound = false;
	}


	// [ FSM ���� ] 
	//MovementStateBase* currentState = GetMovementFSM()->GetCurrentState();
	//if (currentState)
	//{
	//	std::string name = typeid(*currentState).name();  // ���� �̸� Ȯ��
	//	OutputDebugStringA(("���� ����: " + name + "\n").c_str());
	//}
}

void PlayerFSM::FixedUpdate()
{
	movementFSM->FixedUpdate();
}

void PlayerFSM::OnDestroy()
{

}

void PlayerFSM::InputSetting()
{
	isF = Input::GetKeyDown('F');

	//std::string debugStr = "[PlayerFSM] GameManager::Get().canUseMouse : " + std::to_string(GameManager::Get().canUseMouse) + "\n";
	//OutputDebugStringA(debugStr.c_str());

	if (!GameManager::Get().canUseMouse) // ��� �Է°� �ʱ�ȭ
	{
		ResetInputs(); 
		return;
	}

	// [ �Է� ��� ]
	inputX = Input::GetAxisHorizontal();
	inputY = Input::GetAxisVertical();

	isA = Input::GetKey('A');
	isD = Input::GetKey('D');
	isS = Input::GetKey('S');
	isQ = Input::GetKeyDown('Q');
	isE = Input::GetKeyDown('E');
	isShift = Input::GetKey(VK_SHIFT);
	isSpace = Input::GetKeyDown(VK_SPACE);

	// ���콺 �Է�
	isLButton = Input::GetKey(VK_LBUTTON);
	isLButtonDown = Input::GetKeyDown(VK_LBUTTON);
	isLButtonUp = Input::GetKeyUp(VK_LBUTTON);

	isRButton = Input::GetKey(VK_RBUTTON);
	isRButtonDown = Input::GetKeyDown(VK_RBUTTON);
	isRButtonUp = Input::GetKeyUp(VK_RBUTTON);
}

void PlayerFSM::ResetInputs() 
{
	inputX = 0.0f;
	inputY = 0.0f;

	isA = false;
	isD = false;
	isS = false;
	isQ = false;
	isE = false;
	isShift = false;
	isSpace = false;
	// isF = false;

	isLButton = false;
	isLButtonDown = false;
	isLButtonUp = false;
	isRButton = false;
	isRButtonDown = false;
	isRButtonUp = false;
}

void PlayerFSM::FlipXSetting()
{
	if (!isBulletFliping)
	{
		if (abs(rigidbody->velocity.x) > 0.01f)   // ���� ���°� �ƴ� ���� ���� �ݿ�
		{
			spriteRenderer->flipX = rigidbody->velocity.x > 0.0f;  // ���������� �̵� ���̸� flip
			lastFlipX = spriteRenderer->flipX;
		}
		else   spriteRenderer->flipX = lastFlipX;  // �ӵ��� ���� 0�̸� ���� ���� ����
	}
	else { spriteRenderer->flipX = isBulletFlipX; } // BulletTime_State ���� ������ ���� 
}

void PlayerFSM::SpeedSetting()
{
	// Dash ������ �� curSpeed ��� X
	if (movementFSM && movementFSM->IsInState<Dash_State>()) return;

	if (isA || isD)
	{
		curSpeed = (walkSpeed * GetMoveSpeedBonus()) * speedDownRate; // ��ų �رݿ� ���� �߰� �̵� �ӵ�
	}
	else curSpeed = 0;

	 //std::string debugStr = "[PlayerFSM] Current Speed: " + std::to_string(curSpeed) + "\n";
	 //OutputDebugStringA(debugStr.c_str());
}

// �̵��ӵ� ����
void PlayerFSM::SetSpeedDownRate(float rate)
{
	float currentTime = Time::GetTotalTime();

	// ������ ȣ�� ���� 2�� �̳��� ����
	if (currentTime - lastSpeedDownTime < speedDownIgnoreTime) return;

	// ���� ����
	speedDownTimer = speedDownDuration;
	speedDownRate = rate;
	isSpeedDown = true;

	lastSpeedDownTime = currentTime;

	// 0.5�� ���ȸ� �÷��̾� spriteRenderer�� ���� ����
	spriteRenderer->renderMode = RenderMode::UnlitColorTint;
	spriteRenderer->SetBrightness(0.3f);
	speedDownColorTimer = 0.5f; 

	OutputDebugStringA("[PlayerFSM] �ӵ� ���� ����\n");
}

// *-------------- [ Skill ] --------------*

// jump

void PlayerFSM::OnGround()
{
	canAttackAfterJump[JumpPhase::NormalJump] = true;
	canAttackAfterJump[JumpPhase::DoubleJump] = true;
	canAttackAfterJump[JumpPhase::WallJump] = true;

	DebugCanAttack();
}

void PlayerFSM::OnJump(JumpPhase jumpType)
{
	// ���� ���� �ر� ���� 
	if (!GameManager::Get().CheckUnlock(SkillType::JumpAttackExtra))
	{
		// ���� false�� �ʱ�ȭ
		for (auto& pair : canAttackAfterJump) pair.second = false;
	}

	// �ش� ������ true�� ����
	canAttackAfterJump[jumpType] = true;

	DebugCanAttack();
}

bool PlayerFSM::CanAttack()
{
	// ���� ������ ������ ����
	if (GetIsGround())	return true;

	// ���߿����� ���� ���� �� �ϳ��� true�� ���� ����
	for (const auto& pair : canAttackAfterJump)
	{
		if (pair.second) return true;
	}

	return false;
}

void PlayerFSM::OnAirAttack() // � ���� ���¿����� �����ߴٸ� �ش� �÷��׸� ����
{
	for (auto& pair : canAttackAfterJump)
	{
		if (pair.second)
		{
			pair.second = false;
			break; // �� ���� ����
		}
	}

	DebugCanAttack();
}

void PlayerFSM::DebugCanAttack()
{
	std::ostringstream oss;
	oss << "[canAttackAfterJump] ";
	for (const auto& pair : canAttackAfterJump)
	{
		std::string jumpName;
		switch (pair.first)
		{
		case JumpPhase::NormalJump: jumpName = "NormalJump"; break;
		case JumpPhase::DoubleJump: jumpName = "DoubleJump"; break;
		case JumpPhase::WallJump:   jumpName = "WallJump";   break;
		default: jumpName = "Unknown"; break;
		}

		oss << jumpName << "=" << (pair.second ? "true" : "false") << " ";
	}
	oss << "\n";

	OutputDebugStringA(oss.str().c_str());
}


// [ Q E skill ]
void PlayerFSM::TryUseAbsorb() // [ ��� ] 
{
	if (!CanUseAbsorb()){ OutputDebugStringA("[Skill] Q ��� ���� - ��Ÿ�� �Ǵ� �̹� ����\n"); return; }

	targetHon = FindNearestSoulInRange(absorbRange); // ���� ���� ȥ ã�� 
	//std::string debugStr = "[PlayerFSM] Absorb Hunmon's tag = " + targetHon->tag + "\n";
	//OutputDebugStringA(debugStr.c_str());

	if (targetHon)
	{
		targetHon->GetComponent<HonController>()->Absorption(); // ��� ������ �� ȣ�� 

		isAbsorbSkillActive = true; // ȥ ������� ���� 

		absorbCooldownTimer = GetSkillCooldown();

		std::string debugStr = "[PlayerFSM] Q ��ų ��Ÿ�� = " + std::to_string(absorbCooldownTimer) + "\n";
		OutputDebugStringA(debugStr.c_str());

		OutputDebugStringA("[Skill] Q ��� ���� - ��ȥ �����\n");

		GameManager::Get().UseAbsorb();
		GameManager::Get().CanRelease();

		audioSource->SetClip(SFX_Player_Q);
		audioSource->PlayOneShot();
	}
	else
	{
		OutputDebugStringA("[Skill] Q ��� ���� - ���� �� ��ȥ ����\n");
	}
}

void PlayerFSM::TryUseRelease() // [ ���� ] 
{
	if (!CanUseRelease())
	{
		OutputDebugStringA("[Skill] E ���� ���� - ����� ��ȥ ����\n");
		return;
	}

	// Honmun Ž�� & ���� 
	int removedCount = 0;
	for (auto* obj : GameObject::FindAllWithTag("Hon"))
	{
		if (!obj || obj == targetHon) continue; // targetHon ����

		float dist = (obj->GetComponent<Transform>()->GetPosition() - transform->GetPosition()).Magnitude();
		if (dist <= releaseEffectRange)
		{
			obj->GetComponent<HonController>()->TakeDamage(5);
			removedCount++;
		}
	}

	// ���� ����
	hasAbsorbedSoul = false;
	isReleaseSkillAvailable = false;

	// ��ų ����Ʈ ���
	auto anim = GetPlayerSkillEffect()->GetComponent<Animator>();
	if (anim)
	{
		auto skillAnimCtrl = dynamic_cast<SkillAnimatorController*>(anim->controller);
		if (skillAnimCtrl)
		{
			skillAnimCtrl->PlaySkill();
		}
	}

	// �ִϸ��̼� ���� ��ȯ
	playerAnimatorController->SetSkillAvailable(false);

	audioSource->SetClip(SFX_Player_E);
	audioSource->PlayOneShot();

	std::string debugStr = "[Skill] E ���� ���� - " + std::to_string(removedCount) + "�� ȥ ���ŵ�\n";
	OutputDebugStringA(debugStr.c_str());

	GameManager::Get().UseRelease();
}

GameObject* PlayerFSM::FindNearestSoulInRange(float range)
{
	GameObject* closestSoul = nullptr;
	float closestDist = FLT_MAX;

	for (auto* obj : GameObject::FindAllWithTag("Hon"))
	{
		if( obj->name == "HonD" || obj->GetComponent<HonController>()->destroyPending) continue;

		float dist = (obj->GetComponent<Transform>()->GetPosition() - transform->GetPosition()).Magnitude();
		if (dist < range && dist < closestDist)
		{
			closestSoul = obj;
			closestDist = dist;
		}
	}
	return closestSoul;
}

void PlayerFSM::AttractionTargetHon()
{
	if (!targetHon) return;

	honTimer += Time::GetDeltaTime();

	// Ÿ�� ȥ - �÷��̾� ������ �ٰ�����
	Vector2 targetPosition = this->transform->GetPosition();
	Vector2 currentPosition = targetHon->GetComponent<Transform>()->GetPosition();

	float speed = 10.0f; // ȥ �̵� �ӵ� 
	Vector2 newPosition = Vector2::Lerp(currentPosition, targetPosition, speed * Time::GetDeltaTime());
	targetHon->GetComponent<Transform>()->SetPosition(newPosition);

	// ȥ ũ�� ���� �ӵ�
	float scaleSpeed = 8.0f; 
	Vector2 currentScale = targetHon->GetComponent<Transform>()->GetScale();

	Vector2 newScale = Vector2(
		currentScale.x - scaleSpeed * Time::GetDeltaTime(),
		currentScale.y - scaleSpeed * Time::GetDeltaTime()
	);

	// �ּ� ũ�� ���� (Scale�� 0 �̸� X)
	if (newScale.x < 0.1f) newScale.x = 0.1f;
	if (newScale.y < 0.1f) newScale.y = 0.1f;

	// ũ�� ������Ʈ
	targetHon->GetComponent<Transform>()->SetScale(newScale);

	float distanceToPlayer = (targetPosition - currentPosition).Magnitude(); 
	float removeDistanceThreshold = 70.0f;  
	if (distanceToPlayer < removeDistanceThreshold || honTimer >= honQLifetime)
	{
		targetHon->Destroy();  // ȥ ����

		isAbsorbSkillActive = false;

		hasAbsorbedSoul = true;
		isReleaseSkillAvailable = true;
	}
}

void PlayerFSM::UpdateSkillCooldowns()
{
	if (absorbCooldownTimer > 0.0f)
	{
		GameManager::Get().absorbCoolTime = (absorbCooldownTimer -= Time::GetDeltaTime());
	}
	else if(GameManager::Get().canUseAbsorb == false) GameManager::Get().CanAbsorb();
}

bool PlayerFSM::CanUseAbsorb() const
{
	return absorbCooldownTimer <= 0.0f && !hasAbsorbedSoul;
}

bool PlayerFSM::CanUseRelease() const
{
	return hasAbsorbedSoul;
}

// *-------------- [ Collider ] --------------*

void PlayerFSM::OnTriggerEnter(ICollider* other, const ContactInfo& contact)
{
	if (other->gameObject->name == "Hon")
	{

	}
}

void PlayerFSM::OnTriggerStay(ICollider* other, const ContactInfo& contact)
{
	// mo_dev
	if (other->gameObject->name == "NPC" && !GameManager::Get().g_playUI->ChatActiveCheck()
		&& !GameManager::Get().isWave && Input::GetKey('F') && !GameManager::Get().isQuest)
	{
		// GameManager::Get().g_playUI->ChatSetActive(true);
		GameManager::Get().OnNPCInteraction();
	}
}

void PlayerFSM::OnTriggerExit(ICollider* other, const ContactInfo& contact)
{

}


void PlayerFSM::OnCollisionEnter(ICollider* other, const ContactInfo& contact)
{
	if (other->gameObject->name == "Ground" && contact.normal.y > 0.5)
	{
		// OutputDebugStringA("Ground�� �浹 �߽��ϴ�.\n");

		// ���߿��� ������ ��츸 ó��
		if (!isGround)
		{
			isGround = true; 

			PlayLandingEffect(); // ���� ����Ʈ
			landingSound = true;
		}
	}
	else if (other->gameObject->name == "Wall")
	{
		// ���� ����� �÷��̾� �Ʒ��� �浹
		if (contact.normal.y > 0.5)
		{
			// OutputDebugStringA("���� ���κп� �浹�߽��ϴ�.\n");
			isGround = true;
		}
		else
		{
			// OutputDebugStringA("Wall�� �浹 �߽��ϴ�.\n");
			isWall = true;
			if (contact.normal.x == 1) { isWallLeft = true; }
			if (contact.normal.x == -1) { isWallRight = true; }
		}
		
	}
}

void PlayerFSM::OnCollisionStay(ICollider* other, const ContactInfo& contact)
{

}

void PlayerFSM::OnCollisionExit(ICollider* other, const ContactInfo& contact)
{
	if (other->gameObject->name == "Ground" && contact.normal.y > 0.5)
	{
		// OutputDebugStringA("Ground ���������� .\n");
		isGround = false;
	}
	else if (other->gameObject->name == "Wall")
	{
		if (contact.normal.y > 0.5)
		{
			// OutputDebugStringA("���� ���κ� ����������.\n");
			isGround = false;
		}
		else
		{
			isWall = false;
			if (contact.normal.x == 1)   isWallLeft = false;
			if (contact.normal.x == -1)  isWallRight = false;
		}
	}
}


// *-------------- [ GameManager - Skill ] ------------------*

float PlayerFSM::GetMoveSpeedBonus() const
{
	float bonus = GameManager::Get().GetSkillBonus(SkillType::MoveSpeedUp);
	return (bonus > 0.0f) ? bonus : 1.0f;
}

float PlayerFSM::GetAttackRangeBonus() const
{
	// return GameManager::Get().GetSkillBonus(SkillType::AttackRangeUp);

	float bonus = GameManager::Get().GetSkillBonus(SkillType::AttackRangeUp);
	return ((bonus) > (1.0f)) ? (bonus) : (1.0f);
}

float PlayerFSM::GetSkillCooldown() const
{
	float baseCooldown = absorbCooldown; // �⺻ ��Ÿ��
	float cooldownReduction = GameManager::Get().GetSkillBonus(SkillType::SkillCooldownDown); 
	return ((0.0f) > (baseCooldown - cooldownReduction)) ? (0.0f) : (baseCooldown - cooldownReduction); // std::max
} 

float PlayerFSM::GetDashCooldown() const
{
	float baseCooldown = dashCooldown; // �⺻ ��Ÿ��
	float cooldownReduction = GameManager::Get().GetSkillBonus(SkillType::Dash);
	return ((0.0f) > (baseCooldown - cooldownReduction)) ? (0.0f) : (baseCooldown - cooldownReduction); // std::max
}


// [ dash ��Ÿ�� ������Ʈ ]
void PlayerFSM::UpdateDashCooldown()
{
	if (dashCooldownTimer > 0.0f)
	{
		dashCooldownTimer -= Time::GetDeltaTime();  
		if (dashCooldownTimer < 0.0f) dashCooldownTimer = 0.0f;
	}

	//std::string debugStr = "[PlayerFSM] ���� Dash ��Ÿ�� = " + std::to_string(dashCooldownTimer) + "\n";
	//OutputDebugStringA(debugStr.c_str());
}

bool PlayerFSM::CanDash() const
{
	return dashCooldownTimer <= 0.0f;  // ���� ��Ÿ���� 0�̸� ����
}

void PlayerFSM::ResetDashCooldown()
{
	dashCooldownTimer = GetDashCooldown(); // ���� ��ų ���� �ݿ�
}


// -------------------------


void PlayerFSM::PlayLandingEffect()
{
	auto landingEffect = GameObject::Find("PlayerLandingEffect");
	if (!landingEffect) return;

	auto tr = landingEffect->GetComponent<Transform>();
	// tr->SetPosition(transform->GetWorldPosition() + Vector2(7, -85)); 

	auto renderer = landingEffect->GetComponent<SpriteRenderer>();
	renderer->flipX = spriteRenderer->flipX; 

	Vector2 offset = lastFlipX ? Vector2(-8, -90) : Vector2(8, -90);
	tr->SetPosition(transform->GetWorldPosition() + offset);

	auto anim = landingEffect->GetComponent<Animator>();
	if (anim)
	{
		auto landingAnimCtrl = dynamic_cast<LandingAnimatorController*>(anim->controller);
		if (landingAnimCtrl)
		{
			landingAnimCtrl->PlayLanding();
		}
	}
}