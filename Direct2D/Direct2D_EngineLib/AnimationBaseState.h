#pragma once
#include "AnimationClip.h"

/* [AnimationBaseState]
* AnimatorController의 FSM에 등록될 Base State
* 게임 콘텐츠에서 Animation Clip별 State를 생성하고, FSM 상태 전환 로직을 작성하면 된다.
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

