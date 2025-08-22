#pragma once
#include "HonController.h"

/* [D] Luna �޺��� ȥ ��Ʈ�ѷ� Script */
// �������
// 1. A : �ı�
// 2. B : �ı�
// 3. C : �ı�
// 4. D : �ı�

class HonDController : public HonController
{
public:
	HonDController()
	{
		honType = HonType::D;

		hp = 1;
		size = 0.5;
		descentSpeed = 128;

		// gamemanager �浹 ��Ÿ� ����
		int level = GameManager::Get().skillTree[SkillType::KnockbackDistanceUp].unlockLevel;
		if (level != 0)
		{
			SetSpeedUpRate(GameManager::Get().skillValue[SkillType::KnockbackDistanceUp][level - 1]);
		}
	}

	// script component cycle
	void Awake() override;
	void Update() override;

	// trigger event
	void OnTriggerEnter(ICollider* other, const ContactInfo& contact) override;

	// player attack
	void TakeDamageByPlayer(Vector2 dir) override;
};

