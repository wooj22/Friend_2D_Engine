#pragma once
#include <iostream>
#include "AnimationClip.h"
#include "AnimationBaseState.h"
#include "Animator.h"

/* [AnimatorController Asset]
* Animation State Machine (FSM)
* State�� �����ϸ�, ���� AnimationClip�� �������� ����Ѵ�.
* AnimationState���� ������ State�� ��ȯ�Ͽ�, State�� Enter(), Update(), Exit()�� ȣ���Ѵ�.
* Transition(����)�� Ȱ��� ������ �����ϰ�, State���� ���� ������ Ȱ���Ͽ� State�� ��ȯ�� �� �ֵ��� �Ѵ�.
* ���� ���������� �� class�� ��ӹ��� AnimationController�� State�� ����Ͽ� Ȱ���ϸ� �ȴ�..
* ex) class PlayerAnimationController : public AnimatorController{}
*     -> �� �ȿ��� animation clip�� state�� �����ϸ� �ȴ�.
*        �׷� GameObject�ʿ����� �̸� ������ ��Ʈ�ѷ��� ������Ű�� ����ϰ� ������
*/

class AnimatorController
{
public:
    // animation
    AnimationBaseState* curState = nullptr;     // animation clip state
    float currentTime = 0.0f;                   // current time (clip start time cheak)
    int currentFrameIndex = 0;                  // current frame
    bool playing = false;                       // loop/stop

public:
    // conditions
    unordered_map<string, bool> map_boolParams;
    unordered_map<string, float> map_floatParams;
    unordered_map<string, int> map_intParams;

protected:
    // clip state map <name, state>
    unordered_map<string, AnimationBaseState*> map_state;    

public:
    AnimatorController() = default;
    virtual ~AnimatorController() = default;

    void Update(float deltaTime);               // frame update
    void AddState(AnimationBaseState* state);   // add state(state)
    void PlayAnimation(const string& clipName); // play animation("clip name")
    void ChangeAnimation(AnimationBaseState* state); // change animation(state)
    shared_ptr<Sprite> GetCurrentSprite(); // get sprite

public:
    // conditions
    void SetBool(const string& name, bool value);
    bool GetBool(const string& name);
    void SetFloat(const string& name, float value);
    float GetFloat(const string& name);
    void SetInt(const string& name, int value);
    int GetInt(const string& name);
};