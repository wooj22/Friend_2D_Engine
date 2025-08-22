#pragma once
#include "../Friend_2D_EngineLib/Script.h"
#include "../Friend_2D_EngineLib/UI_Text.h"
#include "GameManager.h"
#include "PlayUI.h"


struct WaveChatGroup {
	int Index;
	ChatCondition condition;
	std::vector<std::wstring> lines;
}; 

struct ChatStep {
	ChatCondition condition;
	int index; // ��ȭ ID or ����Ʈ ID
};


class Chat : public Script
{
private:
	std::vector<WaveChatGroup> chatGroups;
	std::vector<std::wstring> currentLines;
	std::vector<ChatStep> sequence;
	ChatCondition curchatCondition;
	int chatCount = 0;				// ��ȭ ī��Ʈ 
	bool finished = false;
	UI_Text* chatText;
	int sequenceCount = 0;

public:
	Chat();
	void Awake() override;
	void Update() override;
	void NextChat();
	void AddChat(int waveIndex, ChatCondition condition, const std::wstring& line);
	void AddChatCount() { chatCount++; }
	void SetSequenceCount(int num) { sequenceCount = num; }
	void SetFinished(bool value) { finished = value; }
	bool GetFinished() { return finished; }
	int GetLineSize() { return currentLines.size(); }
	ChatCondition GetChatCondition() { return curchatCondition; }
	void SetCondition(ChatCondition chatCondition = ChatCondition::Quest);
};

