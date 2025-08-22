#pragma once
#include "../Friend_2D_EngineLib/AnimationClip.h"
#include "../Friend_2D_EngineLib/AnimationBaseState.h"
#include "../Friend_2D_EngineLib/AnimatorController.h"
#include "../Friend_2D_EngineLib/ResourceManager.h"
#include "../Friend_2D_EngineLib/SpriteRenderer.h"

class LandingEffectClip : public AnimationClip
{
public:
	LandingEffectClip()
	{
		name = "Player_Landing_Effect";
		loop = false;
		duration = 0.3f;
		const std::string basePath = "../Resource/Moon/Texture/Player_Landing_Effect/";
		const int frameCount = 8;
		const float frameTime = duration / frameCount;
		for (int i = 0; i < frameCount; ++i)
		{
			char filename[256];
			sprintf_s(filename, "%sLanding (%d).png", basePath.c_str(), i);

			auto texture = ResourceManager::Get().CreateTexture2D(filename);
			auto sprite = ResourceManager::Get().CreateSprite(texture, "Landing_" + std::to_string(i));

			AnimationFrame frame;
			frame.sprite = sprite;
			frame.time = i * frameTime;
			frames.push_back(frame);
		}
	}
	~LandingEffectClip() override {}
};


class LandingEffectState : public AnimationBaseState
{
public:
	LandingEffectState(AnimationClip* c, AnimatorController* ac) : AnimationBaseState(c, ac) {}

private:
	SpriteRenderer* spriteRenderer;

	void Enter() override
    {
		spriteRenderer = GameObject::Find("PlayerLandingEffect")->GetComponent<SpriteRenderer>();

        if (spriteRenderer)  spriteRenderer->SetAlpha(1.0f); // ���� �ʱ�ȭ
    }

    void Update(float dt) override
    {
		if (!spriteRenderer) return;

		int frameIndex = clip->GetFrameIndexAtTime(controller->currentTime);
		int totalFrames = static_cast<int>(clip->frames.size());

		float alpha = 1.0f;

		if (frameIndex >= 2) // 3��° �����Ӻ��� ���� 
		{
			int fadeFrames = totalFrames - 3; // 3��°���� ������ �� �����ӱ���
			float t = static_cast<float>(frameIndex - 2) / fadeFrames; // 0~1
			alpha = 1.0f - t * 0.9f; // ������ ������ 0.1
		}

		spriteRenderer->SetAlpha(alpha);

		if (!clip->loop && frameIndex == totalFrames - 1)
		{
			controller->playing = false;
			controller->ChangeAnimation(nullptr);
			spriteRenderer->SetAlpha(1.0f);
		}
    }

    void Exit() override
    {
        if (spriteRenderer)  spriteRenderer->SetAlpha(1.0f); // ���� ����
    }
};


class LandingAnimatorController : public AnimatorController
{
	LandingEffectClip* landingClip = nullptr;
	LandingEffectState* landingEffectState = nullptr;

public:
	LandingAnimatorController()
	{
		// [ clip ���� ]
		landingClip = new LandingEffectClip();

		// [ state ���� ]
		landingEffectState = new LandingEffectState(landingClip, this);

		// [ state ��� ]
		AddState(landingEffectState);

		// �ʱ� ���� X 
		curState = nullptr;
	}

	// ����/���� �ִϸ��̼� ���
	void PlayLanding()
	{
		// OutputDebugStringA("[LandingAnimatorController] Landing Animation Start\n");
		ChangeAnimation(landingEffectState);
	}

	~LandingAnimatorController() override
	{
		// [ clip ���� ]
		delete landingClip;
		delete landingEffectState;
	}
};