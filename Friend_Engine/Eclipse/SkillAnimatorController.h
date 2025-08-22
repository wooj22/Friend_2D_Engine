#pragma once
#include "../Friend_2D_EngineLib/AnimationClip.h"
#include "../Friend_2D_EngineLib/AnimationBaseState.h"
#include "../Friend_2D_EngineLib/AnimatorController.h"
#include "../Friend_2D_EngineLib/ResourceManager.h"


class SkillEffectClip : public AnimationClip
{
public:
	SkillEffectClip()
	{
		name = "Player_Skill_Effect";
		loop = false;
		duration = 0.5f;
		const std::string basePath = "../Resource/Moon/Texture/Player_Skill_Effect/";
		const int frameCount = 8;
		const float frameTime = duration / frameCount;
		for (int i = 0; i < frameCount; ++i)
		{
			char filename[256];
			sprintf_s(filename, "%sSkill (%d).png", basePath.c_str(), i);

			auto texture = ResourceManager::Get().CreateTexture2D(filename);
			auto sprite = ResourceManager::Get().CreateSprite(texture, "Skill_" + std::to_string(i));

			AnimationFrame frame;
			frame.sprite = sprite;
			frame.time = i * frameTime;
			frames.push_back(frame);
		}
	}
	~SkillEffectClip() override {}
};


class SkillEffectState : public AnimationBaseState
{
public:
	SkillEffectState(AnimationClip* c, AnimatorController* ac) : AnimationBaseState(c, ac) {}

	void Enter() override {}

	void Update(float dt) override
	{
		// ������ �����ӱ��� ����� ������ ����
		if (!clip->loop && clip->GetFrameIndexAtTime(controller->currentTime) == clip->frames.size() - 1)
		{
			controller->playing = false;
			controller->ChangeAnimation(nullptr);  // ���� �ʱ�ȭ
		}
	}
	void Exit() override {}
};


class SkillAnimatorController : public AnimatorController
{
	SkillEffectClip* skillClip = nullptr;
	SkillEffectState* skillEffectState = nullptr;

public:
	SkillAnimatorController()
	{
		// [ clip ���� ]
		skillClip = new SkillEffectClip();

		// [ state ���� ]
		skillEffectState = new SkillEffectState(skillClip, this);

		// [ state ��� ]
		AddState(skillEffectState);

		// �ʱ� ���� X 
		curState = nullptr;
	}

	// ��ų �ִϸ��̼� ���
	void PlaySkill()
	{
		ChangeAnimation(skillEffectState);
	}

	~SkillAnimatorController() override
	{
		// [ clip ���� ]
		delete skillClip;
		delete skillEffectState;
	}
};