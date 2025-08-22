#pragma once
#include "AnimationClip.h"

/* [AnimationBaseState]
* AnimatorController�� FSM�� ��ϵ� Base State
* ���� ���������� Animation Clip�� State�� �����ϰ�, FSM ���� ��ȯ ������ �ۼ��ϸ� �ȴ�.
* Frame�� AnimatorController���� update�ϰ� �����Ƿ� state ���ο�����
* ���� ������ �־� �ٸ� animation state�� ��ȯ�ϴ� ������ �ۼ��ϰ�,    // ���� �ܺο��� PlayAnimation�ص� �ȴ�.
* Sound, Effect���� Ÿ�̹��� ���߾� ����ϴ� �ڵ带 �ۼ��� �� �ִ�.
*/

class AnimatorController;
class AnimationBaseState
{
public:
    AnimationClip* clip = nullptr;                  // clip state
    AnimatorController* controller = nullptr;       // state�� ��ϵ� controller ���� - �������ǰ� get
    
    AnimationBaseState(AnimationClip* c, AnimatorController* ac) : 
        clip(c), controller(ac) {}
    virtual ~AnimationBaseState() = default;

    // animator controller���� ȣ��
    virtual void Enter() = 0;
    virtual void Update(float dt) = 0;
    virtual void Exit() = 0;
};

