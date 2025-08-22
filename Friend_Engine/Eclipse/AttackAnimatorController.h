#pragma once
#include "../Friend_2D_EngineLib/AnimationClip.h"
#include "../Friend_2D_EngineLib/AnimationBaseState.h"
#include "../Friend_2D_EngineLib/AnimatorController.h"
#include "../Friend_2D_EngineLib/ResourceManager.h"


class AttackEffectClip : public AnimationClip
{
public:
	AttackEffectClip()
	{
		name = "Player_Attack_Effect";
		loop = false;
		duration = 0.3f;
		const std::string basePath = "../Resource/Moon/Texture/Player_Attack_Effect/";
		const int frameCount = 11;

		// �����Ӻ� ���� �ٸ� �ð� ���� ����
		float shortTime = 1.0f;  // �⺻ ����ġ
		float longTime = 2.0f;   // ������ ���̴� ����ġ

		// �� ������ ����ġ �迭 (�� 11��)
		std::vector<float> weights;
		for (int i = 0; i < frameCount; ++i)
		{
			if (i < 4)         weights.push_back(longTime); // �� 4������
			else if (i > 6)    weights.push_back(longTime); // �� 4������
			else               weights.push_back(shortTime); // �߰� 3������
		}

		// ��ü ����ġ ��
		float totalWeight = 0.0f;
		for (float w : weights) totalWeight += w;

		// ����ġ ������ ������ �ð� ���
		float accumulatedTime = 0.0f;
		for (int i = 0; i < frameCount; ++i)
		{
			char filename[256];
			sprintf_s(filename, "%sAttack (%d).png", basePath.c_str(), i);

			auto texture = ResourceManager::Get().CreateTexture2D(filename);
			auto sprite = ResourceManager::Get().CreateSprite(texture, "Attack_" + std::to_string(i));

			AnimationFrame frame;
			frame.sprite = sprite;
			frame.time = accumulatedTime;

			// ���� ������ ���� �ð� ����
			accumulatedTime += (weights[i] / totalWeight) * duration;

			frames.push_back(frame);
		}
	}
	~AttackEffectClip() override {}
};



class AttackEffectState : public AnimationBaseState
{
public:
	AttackEffectState(AnimationClip* c, AnimatorController* ac) : AnimationBaseState(c, ac) {}

	void Enter() override {}

	void Update(float dt) override
	{
		// ������ �����ӱ��� ����� ������ ����
		//if (!clip->loop && clip->GetFrameIndexAtTime(controller->currentTime) == clip->frames.size() - 1)
		//{
		//	controller->playing = false;
		//	controller->ChangeAnimation(nullptr);  // ���� �ʱ�ȭ
		//}
	}
	void Exit() override {}
};


class AttackAnimatorController : public AnimatorController
{
	AttackEffectClip* attackClip = nullptr;
	AttackEffectState* attackEffectState = nullptr;

public:
	AttackAnimatorController()
	{
		// [ clip ���� ]
		attackClip = new AttackEffectClip();

		// [ state ���� ]
		attackEffectState = new AttackEffectState(attackClip, this);
		
		// [ state ��� ]
		AddState(attackEffectState);

		// �ʱ� ���� X 
		curState = nullptr;
	}

	// ���� �ִϸ��̼� ���
	void PlayAttack()
	{
		ChangeAnimation(attackEffectState);
	}

	~AttackAnimatorController() override
	{
		// [ clip ���� ]
		delete attackClip;
		delete attackEffectState;
	}
};