#pragma once
#include "HonController.h"

/* [A] Ignis ���� ȥ ��Ʈ�ѷ� Script */
// �������
// 1. A : �� ������Ʈ�� ������ (ũ�� +10%, �ϰ��ӵ� -20%)
// 2. B : �浹 �ݴ� �������� ƨ��
// 3. C : �¿�� ƨ��
// 4. D : �ı�

class HonAController : public HonController
{
public:
	HonAController()
	{
		honType = HonType::A;

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

	// player attack
	void TakeDamageByPlayer(Vector2 dir) override;
};

