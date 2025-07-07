#pragma once
#include "Component.h"
#include "AnimatorSystem.h"

/* [Animator Component]
* GameObject에 부착되어 지정된 AnimatorController를 Update시키고,
* SpriteRenderer의 sprite를 update해주는 컴포넌트
* 즉 SpriteRenderer와 AnimationController의 중간다리 역할
* 'Animator'->AnimatorController->State->clip->'sprite'
*/

class AnimatorController;
class SpriteRenderer;

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
    }  

    void OnEnable() override;
    void Update();
    void OnDestroy() override;

public:
    void SetController(AnimatorController* newController);
};

