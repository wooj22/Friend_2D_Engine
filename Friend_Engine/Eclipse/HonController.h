#pragma once
#include "../Direct2D_EngineLib/Script.h"
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Time.h"
#include "../Direct2D_EngineLib/Vector2.h"
#include "../Direct2D_EngineLib/Transform.h"
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/CircleCollider.h"
#include "../Direct2D_EngineLib/AudioClip.h"
#include "../Direct2D_EngineLib/AudioSource.h"
#include "../Direct2D_EngineLib/ResourceManager.h"
#include "GameManager.h"
#include "PlayerFSM.h"
#include "Attack_State.h"
#include "HonCollisionEffect.h"
#include "BossHitEffect.h"


/* Hon Type Enum */
enum class HonType
{
	A,B,C,D, NONE
};

/* Hon A, B, C, D Controller Base */
class HonController : public Script
{
public:
	HonType honType = HonType::NONE;
	bool isCollisionD = false;
	float is2A = false;
	float isb = false;

public:
	bool destroyPending = false;		// sound delay

protected:
	// hon stat
	int hp = 5;
	float size = 1;
	float descentSpeed = 90;						// �ϰ� speed
	float collisionSpeed = 1000;					// �浹 �и� speed
	const float collisionSpeedDefalut = 1000;		// �浹 �и� �⺻ speed

	// data
	float collisionMovingTime = 0.5f;		// �浹 �и� ���ӽð�
	float pullMovingTime = 0.2f;			// Hon C ������ ���ӽð�

	// controll
	Vector2 moveDirection = Vector2::zero;		// colliison move dir
	Vector2 descentDirection = Vector2::down;	// �ϰ� dir
	Vector2 pullDirection = Vector2::zero;		// Hon C ������ dir
	bool isCollisionMoving = false;				// �浹�� �з����� �ִ� ����
	bool isPullMoving = false;				    // C���� ������� �ִ� ����
	bool isAbsorption = false;					// �÷��̾�� ����ǰ� �ִ� ���� (D�� �Ⱦ����� �÷��̾��� ȣ�� ���ϼ��� ����)

	// delta
	float collisionMovingDelta = 0.0f;
	float pullMovingDelta = 0.0f;

	// hp alpha data
	float alphaData[6] = { 0, 0.3f, 0.5f, 0.7f, 0.85f,  1.f };

	// asset
	shared_ptr<AudioClip> SFX_HonCollision = nullptr;
	shared_ptr<AudioClip> SFX_HonDestroy = nullptr;
	shared_ptr<AudioClip> SFX_HonSplit = nullptr;
	shared_ptr<AudioClip> SFX_HonMerge = nullptr;

	// player 
	Transform* playerTr = nullptr;
	float palyer_deceleration = 0.1;

	// ref component
	Transform* tr = nullptr;
public:	SpriteRenderer* sr = nullptr;
public:	CircleCollider* collider = nullptr;
protected: AudioSource* audioSource = nullptr;

public:
	HonController();

protected:
	void OpacityDirecting();

public:
	// direction
	void SetDirection(Vector2 dir);
	Vector2 Getdirection();

	// size
	void SetSize(float s);
	float GetSize();

	// collision move speed
	void SetSpeedUpRate(float r);

	// descent speed
	void SetDescentSpeed(float s);
	float GetSDescentpeed();

	// hp
	void SetHp(int h);
	int GetHp();
	void TakeDamage(int damage);
	void Die();

	// player attack
	virtual void TakeDamageByPlayer(Vector2 dir) {}

	// collision moving flag
	void CollisionEnd();
	void CollisionStart();

	// HonC ������� �Լ�
	void HonC_PullMe(Vector2 pos);

	// �÷��̾� ���
	void Absorption();
};

