#pragma once
#include "HonController.h"

/* [B] Umbra �׸����� ȥ ��Ʈ�ѷ� Script */
// �������
// 1. A : �浹 �ݴ� �������� ƨ��
// 2. B : �� ������Ʈ�� 2���� �и� (ũ�� -30%, �ϰ��ӵ� +20%)
// 3. C : ����
// 4. D : �ı� 

class HonBController : public HonController
{
private:
	// hon C-B ��ħ x
	Vector2 honBC_dir;

public:
	HonBController()
	{
		honType = HonType::B;

		// gamemanager �浹 ��Ÿ� ����
		int level = GameManager::Get().skillTree[SkillType::KnockbackDistanceUp].unlockLevel;
		if (level != 0)
		{
			SetSpeedUpRate(GameManager::Get().skillValue[SkillType::KnockbackDistanceUp][level - 1]);
		}
	}

	// script component cycle
	void Awake() override;
	void Start() override;
	void Update() override;
	void OnDestroy() override;

	// trigger event
	void OnTriggerEnter(ICollider* other, const ContactInfo& contact) override;
	void OnTriggerStay(ICollider* other, const ContactInfo& contact) override;

	// player attack
	void TakeDamageByPlayer(Vector2 dir) override;
};

