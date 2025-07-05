#pragma once
#include "Component.h"
#include "AnimatorController.h"
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "Time.h"

/* [Animator Component]
* GameObject에 부착되어 AnimatorController를 실행시키고,
* SpriteRenderer의 sprite를 업데이트해주는 컴포넌트
* Animator->AnimatorController->State->clip
*/

class Animator : public Component
{
public:
    AnimatorController* controller;
    SpriteRenderer* spriteRenderer;

    Animator() = default;
    ~Animator() override { delete controller; }  // Controller를 new로 생성했으면 소멸자에서 삭제

    void OnEnable() override
    {
        spriteRenderer = owner->GetComponent<SpriteRenderer>();
    }

    // Update
    void Update()
    {
        if (!controller) return;

        // animation update (controller->state->clip)
        controller->Update(Time::GetDeltaTime());

        // sprite update
        spriteRenderer->sprite = controller->GetCurrentSprite();
    }

    // Set Animator Controller
    void SetController(AnimatorController* newController)
    {
        if (controller) delete controller;
        controller = newController;
    }
};

