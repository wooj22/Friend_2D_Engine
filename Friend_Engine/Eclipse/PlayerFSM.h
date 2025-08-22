#pragma once
#include<map>

#include "../Direct2D_EngineLib/Script.h"
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/ICollider.h"
#include "../Direct2D_EngineLib/RaycastHit.h"
#include "../Direct2D_EngineLib/ColliderSystem.h"
#include "../Direct2D_EngineLib/ResourceManager.h"
#include "../Direct2D_EngineLib/AudioClip.h"
#include "../Direct2D_EngineLib/AudioSource.h"

// FSM 
#include "MovementFSM.h"
#include "ActionFSM.h"

#include "GameManager.h"



enum class JumpPhase
{
	// None,       // ���߿� �ȶ� ����
	NormalJump,
	DoubleJump,
	WallJump,
	COUNT
};

class Transform;
class SpriteRenderer;
class AnimatorController;
class WorldTextRenderer;
class Rigidbody;
class PlayerAttackArea;
class PlayerAnimatorController;
class PlayerSkillEffect;
class LandingAnimatorController;

class PlayerFSM : public Script
{
private:
	// FSM 
	std::unique_ptr<MovementFSM> movementFSM;
	std::unique_ptr<ActionFSM> actionFSM;

public:
	// Jump - skill 
	std::map<JumpPhase, bool> canAttackAfterJump;

public:
	MovementFSM* GetMovementFSM() { return movementFSM.get(); }
	ActionFSM* GetActionFSM() { return actionFSM.get(); }

private:
	float spawnDelay = 0.1f; // 0.1�� �Է�, FSM, ���� ����

	// stat
	float curSpeed = 0;
	float walkSpeed = 460.0f; // 400.0f;
	float dashSpeed = 0.0f;
	float jumpForce = 2000.0f; // 3000.0f;

	bool isSpeedDownRate = false;

	bool isInvincible = false;	// dash ���� ���� 

	// move
	float inputX, inputY; // x : ���� -1 
	bool isGround;
	bool lastFlipX = false;
	bool isBulletFliping = false;
	bool isBulletFlipX = false;

	bool isWallLeft = false;
	bool isWallRight = false;
	bool isWall = false;

	// key
	bool isA, isD, isS, isShift, isSpace, isQ, isE, isF; // moon_dev

	bool isLButton;      // ���� ���� ����
	bool isLButtonDown;  // �̹� �����ӿ� ����
	bool isLButtonUp;    // �̹� �����ӿ� ��

	bool isRButton;
	bool isRButtonDown;
	bool isRButtonUp;

	// ui
	bool isUIOn = false;

private:
	// component
	Transform* transform = nullptr;
	SpriteRenderer* spriteRenderer = nullptr;
	Rigidbody* rigidbody = nullptr;
	AudioSource* audioSource = nullptr;
	AnimatorController* animatorController = nullptr;
	
	PlayerAttackArea* playerAttackArea = nullptr;
	GameObject* playerAttackParent = nullptr;

	GameObject* targetHon = nullptr;

	PlayerAnimatorController* playerAnimatorController = nullptr;
	PlayerSkillEffect* skillEffect = nullptr;

	LandingAnimatorController* landingAnimatorController = nullptr;

public:
	// [ Audio ]
	shared_ptr<AudioClip> SFX_Player_Jump = nullptr;
	shared_ptr<AudioClip> SFX_Player_Land = nullptr;
	shared_ptr<AudioClip> SFX_Player_Attack = nullptr;
	shared_ptr<AudioClip> SFX_Player_Dash = nullptr;
	shared_ptr<AudioClip> SFX_Player_Move1 = nullptr;
	shared_ptr<AudioClip> SFX_Player_Move2 = nullptr;
	shared_ptr<AudioClip> SFX_Player_Move3 = nullptr;
	shared_ptr<AudioClip> SFX_Player_Move4 = nullptr;
	shared_ptr<AudioClip> SFX_Player_Q = nullptr;
	shared_ptr<AudioClip> SFX_Player_E = nullptr;

	bool landingSound = false;


public:
	// [ FSM ���� ] : GameManager ���� �رݵ� ���� �����ͼ� �� ���¿��� ���� ���� 
	float holdTime = 0.0f;
	float timer = 0.0f;

	bool canDoubleJump = false;             // �ٽ� �� ��� ������ ���������� �ѹ��� ���� 
	bool canHanging = false;				// �ٽ� �� ��� ������ �Ŵ޸���� �ѹ��� ���� 
	bool canFallAttack = false;				// �ٽ� �� ��� ������ ���߿��� ���� ���� 

 	bool isHolding = false;

	const float bulletTimeThreshold = 0.2f; // �Ҹ� Ÿ�� ���� 
	const float bulletTimeDuration = 2.0f;  // �Ҹ� ���� �ð� 
	const float ignoreInputDuration = 1.5f; // �Է� ����

	const float defaultGravity = 230.0f;    // �⺻ �߷� 
	const float fastFallGravity = 400.0f;   // ���� �ϰ� ��, �߷� 
	const float fastFallForce = -3000.0f;
	bool didFastFall = false;   // ���� �ϰ� 1ȸ 
		 
	Vector2 MouseWorldPos;					// �ǽð� ���콺 ���� ��ǥ 

	// attack 
	float maxAttackDistance = 230.0f;       // ���� ��, �ִ� �̵� �Ÿ� 
	float attackDesiredTime = 0.2f;         // ���� �ð� 0.3f -> 0.7f
	Vector2 attackDirection;                // ���� ���� ����
	bool isBulletAttack = false;          // �Ҹ� Ÿ�� ���� ����

	// boss / hon 
	float speedDownTimer = 0.0f;     // ������ �پ��� Ÿ�̸�
	float speedDownDuration = 0.5f;  // �ӵ� ���� ���� �ð� (����)
	float speedDownRate = 1.0f;      // ������ �ӵ� ���� 
	float speedDownIgnoreTime = 2.0f; // �ӵ� ���� ���� �ð� 
	bool isSpeedDown = false;
	float lastSpeedDownTime = -100.0f;
	float speedDownColorTimer = 0.0f; // ���� ���� Ÿ�̸�

public:
	// getter
	bool GetIsGround() const { return isGround; }
	bool GetIsSpace() const { return isSpace; }
	bool GetisShift() const { return isShift; }   
	bool GetIsA() const { return isA; }
	bool GetIsD() const { return isD; }
	bool GetIsS() const { return isS; }
	
	bool GetIsLButton() const { return isLButton; }
	bool GetIsLButtonDown() const { return isLButtonDown; }
	bool GetIsLButtonUp() const { return isLButtonUp; }

	bool GetIsRButton() const { return isRButton; }
	bool GetIsRButtonDown() const { return isRButtonDown; }
	bool GetIsRButtonUp() const { return isRButtonUp; }

	float GetJumpForce() const { return jumpForce; }
	float GetInputX() const { return inputX; }
	float GetCurSpeed() const { return curSpeed; }
	float GetWalkSpeed() const { return walkSpeed; }

	// �̵��ӵ� ����
	void SetSpeedDownRate(float rate);

	bool GetIsWall() const { return isWall; }
	bool GetIsWallLeft() const { return isWallLeft; }
	bool GetIsWallRight() const { return isWallRight; }

	bool GetLastFlipX() const { return lastFlipX; } // true ������, false ���� (���ҽ� ���� �����)
	void SetLastFlipX(bool isFlipX) { lastFlipX = isFlipX; } 
	bool GetisBulletFliping() const { return isBulletFliping; }
	void SetisBulletFliping(bool isBulletTime) { isBulletFliping = isBulletTime; }
	bool GetisBulletFlipX() const { return isBulletFlipX; } // true ���� 
	void SetisBulletFlipX(bool isBulletX) { isBulletFlipX = isBulletX; }
	void SetInvincible(bool value) { isInvincible = value; } // ���� ���� ���� 
	bool GetIsInvincible() const { return isInvincible; }

	Rigidbody* GetRigidbody() const { return rigidbody; }
	AnimatorController* GetAnimatorController() const { return animatorController; }
    Transform* GetTransform() const { return transform; }
	SpriteRenderer* GetSpriteRenderer() const { return spriteRenderer; }
	AudioSource* GetAudioSource() const { return audioSource; }
	PlayerAnimatorController* GetPlayerAnimatorController() const { return playerAnimatorController; }

	void SetPlayerAttackArea(PlayerAttackArea* obj) { playerAttackArea = obj; }
	PlayerAttackArea* GetPlayerAttackArea() const { return playerAttackArea; }
	void SetPlayerAttackParent(GameObject* obj) { playerAttackParent = obj; }
	GameObject* GetPlayerAttackParent() const { return playerAttackParent; }
	void SetPlayerSkillEffect(PlayerSkillEffect* effect) { skillEffect = effect; }
	PlayerSkillEffect* GetPlayerSkillEffect() const { return skillEffect; }

public:
	// script component cycle
	void OnEnable() override;				// ������Ʈ Ȱ��ȭ ����
	void Awake() override;					// ������Ʈ�� ��� ������Ʈ�� ������ ���� ���� 1ȸ ȣ��
	void Start() override;					// Awake() ���� ���� 1ȸ ȣ��
	void Update() override;					// �� ������ �ݺ� ȣ��
	void FixedUpdate() override;			// ���� ������Ʈ 0.02f ���� �ݺ� ȣ��
	void OnDestroy() override;				// ������Ʈ or ������Ʈ �Ҹ� ����

	// trigger
	void OnTriggerEnter(ICollider* other, const ContactInfo& contact) override;
	void OnTriggerStay(ICollider* other, const ContactInfo& contact)  override;
	void OnTriggerExit(ICollider* other, const ContactInfo& contact)  override;

	// collision
	void OnCollisionEnter(ICollider* other, const ContactInfo& contact)  override;
	void OnCollisionStay(ICollider* other, const ContactInfo& contact) override;
	void OnCollisionExit(ICollider* other, const ContactInfo& contact)  override;



public: 
	// [ skill ]
	bool canAttack_Unlock = true;          // �⺻ ���� Ƚ�� (�ر� ���� ���� Ƚ���� �� State���� ����)
	int airAttackCount = 0;

	// dash 
	float dashCooldown = 2.0f;         // ��� ��Ÿ�� (2��)
	float dashCooldownTimer = 0.0f;    // ��� ��Ÿ�� Ÿ�̸�

	void UpdateDashCooldown();
	bool CanDash() const;
	void ResetDashCooldown();
	float GetDashCooldown() const;

	// jump 
	void OnGround();
	void OnJump(JumpPhase jumpType);	// �ش� ���� Ÿ�Ը� true, ������ false
	bool CanAttack();					// ���� ���� ���� �Ǻ�
	void OnAirAttack();					// ���� �� ���� ������ ���� Ÿ���� �÷��� false
	void DebugCanAttack();

	bool isAttackIgnore = false; // ���� �����ð� ���� 

	void PlayLandingEffect();


	// Q ��� 
	bool isAbsorbSkillActive = false;
	float absorbCooldown = 10.0f;		// �⺻ ��Ÿ�� 
	float absorbCooldownTimer = 0.0f;
	float absorbRange = 300.0f;			// ��� ���� 
	bool hasAbsorbedSoul = false;       // ���� ����

	float honTimer = 0.0f;				// ȥ�� ���� �ð� ����
	const float honQLifetime = 1.0f;		// ȥ�� �÷��̾� ������� �ִ� ���� �ð� (��)

	// E ���� 
	bool isReleaseSkillAvailable = false; // ����� ȥ�� �ִ°�? = ���� �����Ѱ�? 
	float releaseEffectRange = 400.0f;

	void UpdateSkillCooldowns();
	bool CanUseAbsorb() const;
	bool CanUseRelease() const;

	void TryUseAbsorb();
	void TryUseRelease();
	GameObject* FindNearestSoulInRange(float range);

public:
	// [ FSM setting ] 
	void InputSetting();
	void ResetInputs();
	void SpeedSetting();
	void FlipXSetting();

	// [ Q Skill ]
	void AttractionTargetHon();

public:
	// [ GameManager - Skill ] 

	float GetMoveSpeedBonus() const; // speed 
	float GetAttackRangeBonus() const; // attack 
	float GetSkillCooldown() const; // skill CoolTime 
};

