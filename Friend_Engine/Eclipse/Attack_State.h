#pragma once
#include "MovementStateBase.h" 
#include "../Friend_2D_EngineLib/Vector2.h"

#include "PlayerAttackArea.h"

class MovementFSM;

class Attack_State : public MovementStateBase
{
    float baseMaxDistance = 0.0f;    // �ִ� �̵� �Ÿ� (playerFSM���� ������)
    float desiredTime = 0.0f;        // ���� �ð�

    float timer = 0.0f;
    float moveSpeed = 0.0f;

    bool airAttack = false;

    Vector2 startPos;
    Vector2 targetPos;
    Vector2 direction;

	bool isAttackStart = false; // ���� ���� ����

    float Lerp(float a, float b, float t) { return a + (b - a) * t; } // �������� 

    // �ܻ�
    float afterimageTimer = 0.0f;
    float afterimageInterval = 0.015f;
    void CreateAfterImage(MovementFSM* fsm);

    // ���� ���� 
    float attackAreaDistance = 100.0f;
    Vector2 attackAreaPosition = { 0, 0 };

public:
    void Enter(MovementFSM* fsm) override;
    void Update(MovementFSM* fsm) override;
    void Exit(MovementFSM* fsm) override;

    void FixedUpdate(MovementFSM* fsm) override;
};