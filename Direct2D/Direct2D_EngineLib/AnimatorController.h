#pragma once
#include "AnimationClip.h"
#include "AnimationBaseState.h"

/* [AnimatorController Asset]
* Animation State Machine (FSM)
* State를 관리하며, 현재 AnimationClip의 프레임을 계산한다.
* AnimationState들을 가지고 State를 전환하여, State의 Enter(), Update(), Exit()를 호출한다.
* 게임 콘텐츠에서 이 class를 상속받은 AnimationController를 정의하여 활용한다.
* TODO :: set int/flaot/bool/trigger
* ex) class PlayerAnimationController : public AnimatorController{}
*     -> 이 안에서 animation clip과 state를 생성하면 된다.
*        그럼 GameObject쪽에서는 미리 정의한 컨트롤러만 생성시키면 깔끔하게 정리됨
*/

class AnimatorController
{
public:
    AnimationBaseState* curState = nullptr;     // animation clip state
    float currentTime = 0.0f;                   // current time (clip start time cheak)
    int currentFrameIndex = 0;                  // current frame
    bool playing = false;                       // loop/stop

private:
    unordered_map<string, AnimationBaseState*> map_state;    // clip state map <name, state>

public:
    AnimatorController() = default;
    virtual ~AnimatorController() = default;

    // frame update
    void Update(float deltaTIme)
    {
        if (!curState || !curState->clip || !playing)
            return;

        // loop cheak
        currentTime += deltaTIme;
        if (currentTime >= curState->clip->duration)
        {
            if (curState->clip->loop) currentTime = 0.0f;   
            else
            {
                currentTime = curState->clip->duration;
                playing = false;
            }
        }

        // frame update
        int frameIndex = 0;
        for (size_t i = 0; i < curState->clip->frames.size(); ++i)
        {
            if (currentTime >= curState->clip->frames[i].time)
                frameIndex = (int)i;
            else
                break;
        }

        currentFrameIndex = frameIndex;
        curState->Update(deltaTIme);
    }

    // add state
    void AddState(AnimationBaseState* state)
    {
        string name = state->clip->name;
        map_state[name] = state;
    }

    // play animation with clip name
    void PlayAnimation(const string& clipName)
    {
        auto it = map_state.find(clipName);
        if (it != map_state.end()) 
            ChangeAnimation(it->second);
        else
            OutputDebugStringA(("clip name이 없습니다. " + clipName + "\n").c_str());
    }

    // animation state(Clip) change
    void ChangeAnimation(AnimationBaseState* state)
    {
        if (curState)
            curState->Exit();

        curState = state;
        currentTime = 0.0f;
        currentFrameIndex = 0;
        playing = true;

        if (curState)
            curState->Enter();
    }

    // get sprite
    shared_ptr<Sprite> GetCurrentSprite() const
    {
        if (!curState || !curState->clip) return nullptr;
        return curState->clip->frames[currentFrameIndex].sprite;
    }
};

