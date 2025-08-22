#include "GameManager.h"
#include "PlayUI.h"
#include "Boss.h"
#include "BossController.h"
#include "Quest.h"
#include "Chat.h"
#include "../Direct2D_EngineLib/InvokeSystem.h"




void GameManager::Init()
{
	g_playUI = nullptr; 
	ReSetData();
}

void GameManager::UnInit()
{
	g_playUI = nullptr;
	skillTree.clear();
	skillValue.clear();
	skillText.clear();
}

void GameManager::ReSetData()	
{
	honCount = 0;
	waveCount = 0;
	questCount = 0;
	questIndex = 0;
	isQuest = false;
	questState = ChatCondition::Quest;
	canUseMouse = true;
	isWave = false;
	g_playUI = nullptr;
	absorbCoolTime = 0;
	canUseAbsorb = false;		
	canUseRelease = false;
	quests = { false, false, false };
	SkillReset();
}

void GameManager::WaveStart()
{
	isWave = true;
	waveCount++;

	questCount = 0;
}

void GameManager::SkillReset()
{
	skillTree.clear();
	skillValue.clear();
	skillText.clear();

	//��ų Ʈ�� �ʱ�ȭ
	skillTree[SkillType::MoveSpeedUp] = { false, 0, 3, SkillType::COUNT, 0,{30,50,80} };
	skillTree[SkillType::AttackRangeUp] = { false, 0, 3, SkillType::MoveSpeedUp, 3,{30,50,80} };
	skillTree[SkillType::KnockbackDistanceUp] = { false, 0, 3, SkillType::AttackRangeUp, 3, {30,50,80} };

	skillTree[SkillType::DoubleJump] = { false, 0, 1, SkillType::COUNT, 0, {100} };
	skillTree[SkillType::WallJump] = { false, 0, 1, SkillType::DoubleJump, 1, { 100 } };
	skillTree[SkillType::JumpAttackExtra] = { false, 0, 1, SkillType::WallJump, 1,{100} };

	skillTree[SkillType::Dash] = { false, 0, 2, SkillType::COUNT, 0,{ 50,100 } };
	skillTree[SkillType::SkillCooldownDown] = { false, 0, 2, SkillType::Dash, 2,{50,100} };
	skillTree[SkillType::FastFall] = { false, 0, 1, SkillType::SkillCooldownDown, 2,{ 100 } };


	//��ų�� �ʱ�ȭ
	skillValue[SkillType::MoveSpeedUp] = { 1.05f,1.1f,1.15f };
	skillValue[SkillType::AttackRangeUp] = { 1.05f,1.1f,1.15f };
	skillValue[SkillType::KnockbackDistanceUp] = { 1.05f,1.1f,1.15f };

	skillValue[SkillType::DoubleJump] = { 1 };
	skillValue[SkillType::WallJump] = { 1 };
	skillValue[SkillType::JumpAttackExtra] = { 1 };

	skillValue[SkillType::Dash] = { 0.5,1 };
	skillValue[SkillType::SkillCooldownDown] = { 2,5 };
	skillValue[SkillType::FastFall] = { 1 };


	//��ų �ؽ�Ʈ �ʱ�ȭ
	skillText[SkillType::MoveSpeedUp] = { L"�̵��ӵ� ����" ,L"�̵� �ӵ���\n       /        /       %\n��ŭ �����Ѵ�." };
	skillText[SkillType::AttackRangeUp] = { L"��Ÿ� ����",L"���� �̵��Ÿ���\n       /        /       %\n��ŭ �����Ѵ�." };
	skillText[SkillType::KnockbackDistanceUp] = { L"��Ÿ� ����",L"��ȥ�� �и��� �Ÿ���\n       /        /       %\n��ŭ �����Ѵ�." };
	
	skillText[SkillType::DoubleJump] = { L"���� ����", L"���߿��� �� �� ��\n������ �� �ִ�." };
	skillText[SkillType::WallJump] = { L"�� ����",L"���� ���� �� �� ��\n������ �� �ִ�." };
	skillText[SkillType::JumpAttackExtra] = { L"�߰� ����" ,L"����, �� ���� ��\n1ȸ �߰� ������ ����������." };

	skillText[SkillType::Dash] = { L"���� ��Ÿ�Ӱ���",L"������ ���� ���ð���\n       /        �ʷ� �����Ѵ�." };
	skillText[SkillType::SkillCooldownDown] = { L"��� ��Ÿ�� ����",L"����� ���� ���ð���\n       /        �ʷ� �����Ѵ�." };
	skillText[SkillType::FastFall] = { L"���� �ϰ�" ,L"SŰ�� ����\n������ �ϰ��� �� �ִ�." };

	

	if (g_playUI != nullptr)
	{
		g_playUI->ResetAllSkillCheat();
	}
}

bool GameManager::CanUnlock(SkillType skill)
{
	const auto& info = skillTree[skill];
	if (info.unlocked)
		return false; // �̹� �رݵ�

	if (info.prerequisiteSkill != SkillType::COUNT) {
		const auto& preInfo = skillTree[info.prerequisiteSkill];
		if (preInfo.unlockLevel < info.requiredLevel)
			return false; // ���� �̴�
	}

	if(info.skillCost[info.unlockLevel] > honCount)
		return false; // ȥ ����

	return true; // ���� ����
}

bool GameManager::LevelUpSkill(SkillType skill, bool check )
{
	auto& info = skillTree[skill];

	// ��ų�� ���� ������� ��
	if (!info.unlocked)
	{
		if (!CanUnlock(skill))
			return false; // ���� �̴�

		honCount -= info.skillCost[info.unlockLevel];
		info.unlocked = true;
		info.unlockLevel = 1;
		if (g_playUI != nullptr)
		{
			g_playUI->ChangeHonCountText();
			g_playUI->SkillActiveSound();
		}
		return true;
	}

	// �̹� �رݵ� ���¿��� ������
	if (info.unlockLevel >= info.maxLevel)
		return false;

	// ȥ ����
	if (info.skillCost[info.unlockLevel] > honCount)
		return false; 

	if (!check)
	{
		honCount -= info.skillCost[info.unlockLevel];
		info.unlockLevel++;
		if(g_playUI != nullptr) g_playUI->ChangeHonCountText();
	}
	return true;
}

void GameManager::AllSkillUnlock()
{
	for (auto& pair : skillTree)
	{
		SkillInfo& info = pair.second;
		info.unlocked = true;
		info.unlockLevel = info.maxLevel;
	}

	if (g_playUI !=nullptr)
	{
		g_playUI->AllSkillCheat();
	}
}

void GameManager::ChangeHonCount(int num)
{
	honCount += num;
	if (honCount < 0) honCount = 0;
	g_playUI->ChangeHonCountText();
}

void GameManager::CanAbsorb()
{
	canUseAbsorb = true;
	g_playUI->ActivateAbsorb();
}

void GameManager::UseAbsorb()
{
	canUseAbsorb = false;
	g_playUI->DeactivateAbsorb();
}

void GameManager::CanRelease()
{
	canUseRelease = true;
	g_playUI->ActivateRelease();
}

void GameManager::UseRelease()
{
	canUseRelease = false;
	g_playUI->DeactivateRelease();
}

void GameManager::FinishWave()
{
	g_playUI->timer_Text->screenTextRenderer->SetText(L"00");

	if (questState != ChatCondition::Success)
	{
		g_playUI->quest->QuestFail();
		if (waveCount == 4)
		{
			g_playUI->fade->FadeOut();
			GameManager::Get().canUseMouse = false;
			InvokeSystem::Invoke(4.0f, [this]() {
				g_playUI->FailEvent();
				});
			InvokeSystem::Invoke(6.0f, []() {
				SceneManager::Get().ChangeScene(6);
				});
			return;
		}
	}
	else
	{
		g_playUI->quest->QuestSuccess();
		if (waveCount == 4)
		{
			g_playUI->fade->FadeOut();
			GameManager::Get().canUseMouse = false;
			InvokeSystem::Invoke(4.0f, [this]() {
				g_playUI->SuccessEvent();
				});

			InvokeSystem::Invoke(6.0f, [this]() {
				g_playUI->success_Text->SetActive(false);
				g_playUI->stop_Button->SetActive(true);
				GameManager::Get().canUseMouse = true;
				g_playUI->stop_Button->SetActive(true);
				g_playUI->fade->FadeIn();
				});
		}
	}

	g_playUI->chat->SetCondition(questState);
}

void GameManager::ChangeQuestCount(int waveidx)
{
	if (waveidx == waveCount)
	{
		questCount++;
		g_playUI->quest->RefreshQuestCountText(questCount);
		if (questCount >= g_playUI->quest->GetQuestMaxCount())
		{
			questState = ChatCondition::Success;
			g_playUI->quest->QuestSuccess();
		}
	}
}

void GameManager::CheckQuest(int questidx, int idx)
{
	if (questidx == questIndex)
	{
		quests[idx] = true;

		if (std::all_of(quests.begin(), quests.end(), [](bool q) { return q; }))
		{
			isQuest = false;
			quests = { false, false, false };
		}
	}
}


float GameManager::GetSkillBonus(SkillType type)
{
	auto it = skillTree.find(type);
	if (it == skillTree.end()) return 0.0f;

	int level = it->second.unlockLevel;

	auto valIt = skillValue.find(type);
	if (valIt == skillValue.end()) return 0.0f;

	const std::vector<float>& values = valIt->second;

	if (level <= 0 || values.empty()) return 0.0f;

	// �迭 ���� �ʰ����� �ʵ���
	int index = clamp(level - 1, 0, static_cast<int>(values.size()) - 1);
	return values[index];
}

void GameManager::OnNPCInteraction()
{

	if(GameObject::Find("MoonShadow")->GetComponent<MoonShadowController>()->IsEclipseDirecting()) return;
	g_playUI->ChatSetActive(true);
	canUseMouse = false;
	if(questState == ChatCondition::Success)
		GameManager::Get().ChangeHonCount(g_playUI->quest->QuestReward());
	if (g_playUI->skillWindowBackGround_Image->IsActive())
		g_playUI->skillWindowBackGround_Image->SetActive(false);
	g_playUI->hon_Image->SetActive(false);
	g_playUI->stop_Button->SetActive(false);
	g_playUI->quest_Image->SetActive(false);

	GameObject::Find("InGameCamera")->GetComponent<CameraController>()->ZoomInToPlayer();

	if (g_playUI->chat->GetLineSize() == 1)
	{
		g_playUI->chat->SetFinished(true);
		g_playUI->chat_Button->SetActive(true);
		g_playUI->chatNext_Image->SetActive(false);
	}

	if (waveCount == 4)
	{
		g_playUI->ClearSound();
	}

}

void GameManager::ChangeBossHp(float hp)
{
	if(hp>0)
		g_playUI->bossHP->RefreshBossHp(hp);
	else
		g_playUI->bossHP->RefreshBossHp(0);
}
