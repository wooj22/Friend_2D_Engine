#pragma once
#include "../Direct2D_EngineLib/AnimationClip.h"
#include "../Direct2D_EngineLib/AnimationBaseState.h"
#include "../Direct2D_EngineLib/AnimatorController.h"
#include "../Direct2D_EngineLib/ResourceManager.h"


// 게임 콘텐츠 Animation asset 정의
/*------------ Animation Clip ------------*/
class CatIdleClip : public AnimationClip
{
public:
    CatIdleClip()
    {
        auto texture = ResourceManager::Get().CreateTexture2D("../Resource/Texture/Cat_Idle.png");
        LoadSpriteSheetFromJson(texture, "../Resource/Data/SpriteSheet/Cat_Idle_Sprites.json");
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
        LoadSpriteSheetFromJson(texture, "../Resource/Data/SpriteSheet/Cat_Walk_Sprites.json");
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
        LoadSpriteSheetFromJson(texture, "../Resource/Data/SpriteSheet/Cat_Run_Sprites.json");
        LoadAnimationClipFromJson(texture, "../Resource/Data/AnimationClip/Cat_Run_AniClip.json");
    }
    ~CatRunClip() override {}
};

/*------------ Animation State ------------*/
class CatIdleState : public AnimationBaseState
{
public:
    CatIdleState(AnimationClip* c, AnimatorController* ac) : AnimationBaseState(c, ac) {}

    void Enter() override {}
    void Update(float dt) override
    {
        // tansition
        if (controller->GetFloat("Speed") >= 350.f)
            controller->PlayAnimation("Cat_Run");
        else if (controller->GetFloat("Speed") >= 180.f)
            controller->PlayAnimation("Cat_Walk");
    }
    void Exit() override {}
};

class CatWalkState : public AnimationBaseState
{
public:
    CatWalkState(AnimationClip* c, AnimatorController* ac) : AnimationBaseState(c, ac) {}

    void Enter() override {}
    void Update(float dt) override
    {
        // tansition
        if (controller->GetFloat("Speed") == 0)
            controller->PlayAnimation("Cat_Idle");
        else if (controller->GetFloat("Speed") >= 350.f)
            controller->PlayAnimation("Cat_Run");
    }
    void Exit() override {}
};

class CatRunState : public AnimationBaseState
{
public:
    CatRunState(AnimationClip* c, AnimatorController* ac) :
        AnimationBaseState(c, ac) {
    }

    void Enter() override {}
    void Update(float dt) override
    {
        // tansition
        if (controller->GetFloat("Speed") == 0)
            controller->PlayAnimation("Cat_Idle");
        else if (controller->GetFloat("Speed") < 350.f &&
            controller->GetFloat("Speed") >= 180.f)
            controller->PlayAnimation("Cat_Walk");
    }
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
        // idle clip 생성의 다른 방법
        AnimationClip* clip1 = new AnimationClip();

        // 1) 스프라이트 시트 이미지를 로드하여 생성한다 (단순 이미지 로드)
        auto texture = ResourceManager::Get().CreateTexture2D("../Resource/Texture/Cat_Idle.png");      

        // 2) 스프라이트 시트 데이터를 로드하여 sprite들을 생성한다. (rect별로 잘라서 생성)
        clip1->LoadSpriteSheetFromJson(texture, "../Resource/Data/SpriteSheet/Cat_Idle_Sprites.json");

        // 3) 애니메이션 클립 데이터를 로드하여 저장한다. (어떤 sprite가 몇초에 재생되는지)
        clip1->LoadAnimationClipFromJson(texture, "../Resource/Data/AnimationClip/Cat_Idle_AniClip.json");

        // clip 생성
        //idleClip = new CatIdleClip();
        walkClip = new CatWalkClip();
        runClip = new CatRunClip();

        // state 생성
        idleState = new CatIdleState(clip1, this);
        walkState = new CatWalkState(walkClip, this);
        runState = new CatRunState(runClip, this);

        // state 등록
        AddState(idleState);
        AddState(walkState);
        AddState(runState);

        // 초기 상태
        ChangeAnimation(idleState);
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
};
