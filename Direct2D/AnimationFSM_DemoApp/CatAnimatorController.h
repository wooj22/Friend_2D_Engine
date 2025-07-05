#pragma once
#include "../Direct2D_EngineLib/AnimationClip.h"
#include "../Direct2D_EngineLib/AnimationBaseState.h"
#include "../Direct2D_EngineLib/AnimatorController.h"
#include "../Direct2D_EngineLib/ResourceManager.h"

/*------------ Animation Clip ------------*/
class CatIdleClip : public AnimationClip
{
public:
    CatIdleClip()
    {
        auto texture = ResourceManager::Get().CreateTexture2D("../Resource/Texture/Cat_Idle.png");
        LoadSpritesFromJson(texture, "../Resource/Data/SpriteSheet/Cat_Idle_Sprites.json");
        LoadAnimationClipFromJson(texture, "../Resource/Data/AnimationClip/Cat_Idle_AniClip.json");
    }
    ~CatIdleClip() override {}
};

class CatWalkClip : public AnimationClip
{
public:
    CatWalkClip()
    {
        auto texture = ResourceManager::Get().CreateTexture2D("../Resource/Texture/Cat_Walk.png");
        LoadSpritesFromJson(texture, "../Resource/Data/SpriteSheet/Cat_Walk_Sprites.json");
        LoadAnimationClipFromJson(texture, "../Resource/Data/AnimationClip/Cat_Walk_AniClip.json");
    }
    ~CatWalkClip() override {}
};

class CatRunClip : public AnimationClip
{
public:
    CatRunClip()
    {
        auto texture = ResourceManager::Get().CreateTexture2D("../Resource/Texture/Cat_Run.png");
        LoadSpritesFromJson(texture, "../Resource/Data/SpriteSheet/Cat_Run_Sprites.json");
        LoadAnimationClipFromJson(texture, "../Resource/Data/AnimationClip/Cat_Run_AniClip.json");
    }
    ~CatRunClip() override {}
};

/*------------ Animation State ------------*/
class CatIdleState : public AnimationBaseState
{
public:
    CatIdleState(AnimationClip* clip) : AnimationBaseState(clip) {}

    void Enter() override {}
    void Update(float dt) override {}
    void Exit() override {}
};

class CatWalkState : public AnimationBaseState
{
public:
    CatWalkState(AnimationClip* clip) : AnimationBaseState(clip) {}

    void Enter() override {}
    void Update(float dt) override {}
    void Exit() override {}
};

class CatRunState : public AnimationBaseState
{
public:
    CatRunState(AnimationClip* clip) : AnimationBaseState(clip) {}

    void Enter() override {}
    void Update(float dt) override {}
    void Exit() override {}
};

/*------------ Animation Controller ------------*/
class CatAnimatorController : public AnimatorController
{
public:
    // Clips
    CatIdleClip* idleClip = nullptr;
    CatWalkClip* walkClip = nullptr;
    CatRunClip* runClip = nullptr;

    // States
    CatIdleState* idleState = nullptr;
    CatWalkState* walkState = nullptr;
    CatRunState* runState = nullptr;

public:
    CatAnimatorController()
    {
        // clip 생성
        idleClip = new CatIdleClip();
        walkClip = new CatWalkClip();
        runClip = new CatRunClip();

        // state 생성
        idleState = new CatIdleState(idleClip);
        walkState = new CatWalkState(walkClip);
        runState = new CatRunState(runClip);

        // state 등록
        AddState(idleState);
        AddState(walkState);
        AddState(runState);

        // 초기 상태
        PlayAnimation("Cat_Idle");
        //ChangeAnimation(idleState);
    }

    ~CatAnimatorController() override
    {
        delete idleClip;
        delete walkClip;
        delete runClip;

        delete idleState;
        delete walkState;
        delete runState;
    }

    void ToIdle() { ChangeAnimation(idleState); }
    void ToWalk() { ChangeAnimation(walkState); }
    void ToRun() { ChangeAnimation(runState); }
};
