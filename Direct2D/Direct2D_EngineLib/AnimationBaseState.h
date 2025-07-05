#pragma once
#include "AnimationClip.h"

/* [AnimationBaseState]
* AnimatorController의 FSM에 등록될 Base State
*/

class AnimationBaseState
{
public:
    AnimationClip* clip = nullptr;

    AnimationBaseState(AnimationClip* c) : clip(c) {}
    virtual ~AnimationBaseState() = default;

    virtual void Enter() = 0;
    virtual void Update(float dt) = 0;
    virtual void Exit() = 0;
};

