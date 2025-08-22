#pragma once
#include "Component.h"
#include "AnimatorSystem.h"

/* [Animator Component]
* GameObject�� �����Ǿ� ������ AnimatorController�� Update��Ű��,
* SpriteRenderer�� sprite�� update���ִ� ������Ʈ
* �� SpriteRenderer�� AnimationController�� �߰��ٸ� ����
* 'Animator'->AnimatorController->State->clip->'sprite'
*/

class AnimatorController;
class SpriteRenderer;
class ImageRenderer;

class Animator : public Component
{
public:
    AnimatorController* controller = nullptr;
    SpriteRenderer* spriteRenderer = nullptr;
    ImageRenderer* imageRenderer = nullptr;

public:
    // component cycle
    Animator() = default;
    ~Animator() override {}
    
    void OnEnable_Inner() override final;
    void OnDisable_Inner() override final;
    void Update();
    void OnDestroy_Inner() override final;

public:
    void SetController(AnimatorController* newController);
};

