#pragma once
#include "MovementStateBase.h"

class Jump_Wall_State : public MovementStateBase
{
public:
    void Enter(MovementFSM* fsm) override;
    void Update(MovementFSM* fsm) override;
    void FixedUpdate(MovementFSM* fsm) override;
    void Exit(MovementFSM* fsm) override;

private:
    float wallJumpForce = 1600.0f ;
    float jumpXPower = 500.0f;
    float doubleJumpXPower = 200.0f;

    float elapsedTime = 0.0f;       // ��� �ð�
    float inputBlockTime = 0.05f;   // �Է� ���� �ð�

    float airAcceleration = 20.0f;  // ���� ���ӵ�
    float airFriction = 3.0f;       // ���� ���ӵ�

    float inputX;
    float curVelX;

    int lastWallDir = 0; // -1: ���� ��, 1: ������ ��

    float Lerp(float a, float b, float t) { return a + (b - a) * t; } // �������� 
};