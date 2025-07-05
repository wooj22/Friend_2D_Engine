#pragma once
#include "Component.h"
#include "AnimatorSystem.h"
#include "AnimatorController.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Time.h"

/* [Animator Component]
* GameObject에 부착되어 AnimatorController를 실행시키고,
* SpriteRenderer의 sprite를 업데이트해주는 컴포넌트
* Animator->AnimatorController->State->clip
*/

class AnimatorSystem;
class Animator : public Component
{
public:
    AnimatorController* controller = nullptr;
    SpriteRenderer* spriteRenderer = nullptr;

public:
    // component cycle
    Animator() 
    { 
        AnimatorSystem::Get().Regist(this);
    }
    ~Animator() override 
    { 
        AnimatorSystem::Get().Unregist(this);
        //delete controller;  리소스 매니저 구조로 바꾸기
    }  

    void OnEnable() override;
    void Update();
    void OnDestroy() override;

public:
    void SetController(AnimatorController* newController);
};

