#include "Quest.h"


void Quest::Awake()
{
	questLines.push_back(L"");//���̺� ī���Ϳ� ������ �ε�����
	questLines.push_back(L"���� �̵� (A)\n���� �̵� (D)\n���� (SPACE)");
	questLines.push_back(L"�⺻���� (�� Ŭ��)\n�Ҹ�Ÿ�� (�� Ȧ��)\n��� (SHIFT)");
	questLines.push_back(L"��ȥ�� 10ȸ\nóġ�ϼ���.");
	questLines.push_back(L"TAP�� ���� \n��ų�� ��켼��.");
	questLines.push_back(L"���⸦ 5ȸ\n�����ϼ���.");
	questLines.push_back(L"TAP�� ���� \n��ų�� ��켼��.");
	questLines.push_back(L"�糪�� ��ȣ�ϼ���.");
	questLines.push_back(L"TAP�� ���� \n��ų�� ��켼��.");
	questLines.push_back(L"�콺�� óġ�ϼ���.");

	questMaxCount.push_back(0);//���̺� ī���Ϳ� ������ �ε�����
	questMaxCount.push_back(10);
	questMaxCount.push_back(5);
	questMaxCount.push_back(5);
	questMaxCount.push_back(1);

	questReward.push_back(0);//���̺� ī���Ϳ� ������ �ε�����
	questReward.push_back(100);
	questReward.push_back(150);
	questReward.push_back(200);
	questReward.push_back(0);
}

void Quest::Update()
{

}

void Quest::RefreshQuestText()
{
	if(GameManager::Get().questState != ChatCondition::Quest)
		GameManager::Get().g_playUI->quest_Text->screenTextRenderer->SetText(questLines[GameManager::Get().questIndex]);
	else
	{
		GameManager::Get().g_playUI->quest_Text->screenTextRenderer->SetText(questLines[GameManager::Get().questIndex]);
	}
}

void Quest::RefreshQuestCountText(int num)
{
	if (num == -1)
		GameManager::Get().g_playUI->questCount_Text->screenTextRenderer->SetText(L"");
	else
	{
		GameManager::Get().g_playUI->questCount_Text->screenTextRenderer->SetText(L"[   "+ to_wstring(num) + L"    /    " + to_wstring(questMaxCount[GameManager::Get().waveCount]) + L"   ]");
		GameManager::Get().g_playUI->quest_Text->rectTransform->SetPosition(0, 0);
	}
}

void Quest::QuestSuccess()
{
	GameManager::Get().questState = ChatCondition::Success;
	GameManager::Get().g_playUI->questCount_Text->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::Green));
}

void Quest::QuestFail()
{
	GameManager::Get().questState = ChatCondition::Fail;
	GameManager::Get().g_playUI->questCount_Text->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::Red));
}
