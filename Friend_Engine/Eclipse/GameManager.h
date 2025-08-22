#pragma once
#include "../Direct2D_EngineLib/Singleton.h"
#include "CameraController.h"
#include <unordered_map>
#include <string>  
#include <vector>  

class PlayUI;

enum class ChatCondition { Quest, Wave, Success, Fail  };

enum class SkillType {
	KnockbackDistanceUp,	// 1-1	�浹 ��Ÿ� ����	�ִ� 3
	DoubleJump,				// 1-2	���� ����			�ִ� 1
	WallJump,				// 1-3	�� ����				�ִ� 1

	SkillCooldownDown,		// 2-1	��ų ��Ÿ�� ����	�ִ� 2	
	JumpAttackExtra,		// 2-2	���� �� �߰�����	�ִ� 1
	FastFall,				// 2-3	���� ����			�ִ� 1

	MoveSpeedUp,			// 3-1	�̵��ӵ� ����		�ִ� 3
	AttackRangeUp,			// 3-2	���� �̵��Ÿ� ����	�ִ� 3
	Dash,					// 3-3	���				�ִ� 1

	COUNT				// �� ���� ������
};


// unordered_map�� Ű�� ����ϱ� ���� hash �Լ��� ����
namespace std {
	template<>
	struct hash<SkillType> {
		std::size_t operator()(const SkillType& k) const noexcept {
			return std::hash<int>()(static_cast<int>(k));
		}
	};
}

//UI ��ų �ر� ����
struct SkillInfo {
	bool unlocked = false;  // �ر� ����
	int unlockLevel = 0;    // �رݵ� ���� (Ȥ�� ���� ����)
	int maxLevel = 1;		// ��ų �ִ� ���� (�⺻ 1)

	// ���� ����: optional
	SkillType prerequisiteSkill = SkillType::COUNT; // �⺻�� = ����
	int requiredLevel = 0; // �� ��ų�� �� ���� �̻��� ���� �ر� ����
	std::vector<int> skillCost;

	SkillInfo(
		bool unlocked = false,
		int unlockLevel = 0,
		int maxLevel = 1,
		SkillType prerequisiteSkill = SkillType::COUNT,
		int requiredLevel = 0,
		const std::vector<int>& cost = {})
		: unlocked(unlocked),
		unlockLevel(unlockLevel),
		maxLevel(maxLevel),
		prerequisiteSkill(prerequisiteSkill),
		requiredLevel(requiredLevel),
		skillCost(cost)
	{
	}
};

//UI ��ų ���� ����
struct SkillText {
	std::wstring skillname = L"";				// ��ų �̸�
	std::wstring skillDesc = L"";				// ��ų ����

	SkillText(
		
		std::wstring name = L"",
		std::wstring descriptions = L"")
		: 
		skillname(name),
		skillDesc(descriptions)
	{
	}
};

class GameManager : public Singleton<GameManager>
{

public:
	PlayUI* g_playUI;
	int honCount;

	// ���콺
	bool canUseMouse;

	//���̺�
	int waveCount;				// UI ���� �Ѱ� �� ���̺� ī��Ʈ
	bool isWave;				// UI ���� �Ѱ� �� ���̺� ���� ����
	float waveTime;				// ���̺꿡�� �Ѱ��� ���̺� Ÿ��
	bool isQuest;				// UI ���� �Ѱ� �� ����Ʈ ���� ����

	//����Ʈ
	int questIndex;
	int questCount;
	ChatCondition questState;
	std::vector<bool> quests;

	//�÷��̾� ��ų
	float absorbCoolTime;		// Q ��� ��Ÿ��				
	bool canUseAbsorb;			// Q ��� ��ų ��� ���� ����	
	bool canUseRelease ;		// E ���� ��ų ��� ���� ����	

	std::unordered_map<SkillType, SkillInfo> skillTree;
	std::unordered_map<SkillType, std::vector<float>> skillValue;
	std::unordered_map<SkillType, SkillText> skillText;

	GameManager() = default;
	~GameManager() = default;

	void Init();
	void UnInit();
	void ReSetData();
	void WaveStart();

	// UI��ų ���� �Լ�
	void SkillReset();
	bool CanUnlock(SkillType skill);
	bool CheckUnlock(SkillType skill) { return skillTree[skill].unlocked; }
	bool LevelUpSkill(SkillType skill, bool check = false);
	void AllSkillUnlock();

	// �÷��̾� ��ų ���� �Լ�
	void CanAbsorb();
	void UseAbsorb();
	void CanRelease();
	void UseRelease();


	// ȥ ���� �Լ�
	void ChangeHonCount(int num);

	// ���̺� ���� �Լ�
	void FinishWave();

	// ����Ʈ ���� �Լ�
	void ChangeQuestCount(int waveidx);
	void CheckQuest(int questidx, int idx);

	// ��ų ��ġ �� 
	float GetSkillBonus(SkillType type);

	// NPC ���� �Լ� - ����Ʈ ���� �� ��ȭâ ����
	void OnNPCInteraction();

	// Boss ���� �Լ�
	void ChangeBossHp(float hp);
};