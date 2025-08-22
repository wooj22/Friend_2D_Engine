#pragma once
#include "MovementStateBase.h"

class MovementFSM;

class Fall_State : public MovementStateBase
{
    // ���� �̵�: �ε巴�� ����/����
    float inputX;
    float airAcceleration = 30.0f;     // ���� ���ӵ�
    float airFriction = 3.0f;          // ���� ���ӵ�

    float curVelX;

    float Lerp(float a, float b, float t) { return a + (b - a) * t; } // �������� 

    // �ܻ�
    float afterimageTimer = 0.0f;
    float afterimageInterval = 0.01f;
    void CreateAfterImage(MovementFSM* fsm);

public:
    void Enter(MovementFSM* fsm) override;
    void Update(MovementFSM* fsm) override;
    void Exit(MovementFSM* fsm) override;

    void FixedUpdate(MovementFSM* fsm) override;
};