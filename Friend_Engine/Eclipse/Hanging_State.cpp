#include "Hanging_State.h"
#include "Jump_Wall_State.h"
#include "Jump_State.h"
#include "Idle_State.h"
#include "Fall_State.h"

#include "MovementFSM.h"
#include "PlayerFSM.h"
#include "PlayerAnimatorController.h"
#include "GameManager.h"

#include "../Direct2D_EngineLib/Rigidbody.h"
#include "../Direct2D_EngineLib/Time.h"
#include "BulletTime_State.h"
#include "Attack_State.h"


void Hanging_State::Enter(MovementFSM * fsm)
{
    OutputDebugStringA("[Hanging_State] ���� �Ŵ޸� ���� ����\n");

    // ���� �ӵ��� 0���� (���� �Ŵ޸� ȿ��)
    fsm->GetPlayerFSM()->GetRigidbody()->velocity.y = 0.0f;
    fsm->GetPlayerFSM()->GetRigidbody()->velocity.x = 0.0f;


    // ����: ���� �ִ� ������ �� �ݴ��� ���� Flip
    if ((fsm->GetPlayerFSM()->GetIsWallRight() && fsm->GetPlayerFSM()->GetLastFlipX()) ||
        (fsm->GetPlayerFSM()->GetIsWallLeft() && !fsm->GetPlayerFSM()->GetLastFlipX()))
    {
        fsm->GetPlayerFSM()->SetLastFlipX(!fsm->GetPlayerFSM()->GetLastFlipX());
    }

    fsm->GetPlayerFSM()->GetAnimatorController()->SetBool("Hanging", true);
}

void Hanging_State::Update(MovementFSM* fsm)
{
    // ���� Ű ������ �� ������ ��ȯ
    if (GameManager::Get().CheckUnlock(SkillType::WallJump) && fsm->GetPlayerFSM()->GetIsSpace() )
    {
        fsm->ChangeState(std::make_unique<Jump_Wall_State>());
        return;
    }

    // ���� �������
    if (!fsm->GetPlayerFSM()->GetIsWallLeft() && !fsm->GetPlayerFSM()->GetIsWallRight())
    {
        fsm->ChangeState(std::make_unique<Idle_State>());
        return;
    }

    // �ݴ� ����Ű �Է��ϸ� ������ 
    float inputX = fsm->GetPlayerFSM()->GetInputX();
    if ((fsm->GetPlayerFSM()->GetIsWallLeft() && inputX > 0.5f) || (fsm->GetPlayerFSM()->GetIsWallRight() && inputX < -0.5f))
    {
        fsm->GetPlayerFSM()->SetLastFlipX(!fsm->GetPlayerFSM()->GetLastFlipX());

        fsm->ChangeState(std::make_unique<Fall_State>());
        return;
    }


    // [ Attack / Bullet ]
    if (fsm->GetPlayerFSM()->CanAttack() && fsm->GetPlayerFSM()->GetIsLButton())
    {
        if (!fsm->GetPlayerFSM()->isHolding) { fsm->GetPlayerFSM()->isHolding = true;   fsm->GetPlayerFSM()->holdTime = 0.0f; }

        fsm->GetPlayerFSM()->holdTime += Time::GetDeltaTime();

        // [ BulletTime ]
        if (fsm->GetPlayerFSM()->CanAttack() &&
            fsm->GetPlayerFSM()->holdTime >= fsm->GetPlayerFSM()->bulletTimeThreshold)
        {
            fsm->GetPlayerFSM()->GetMovementFSM()->ChangeState(std::make_unique<BulletTime_State>());
        }
    }
    else
    {
        // [ Attack ]
        if (fsm->GetPlayerFSM()->CanAttack() &&
            fsm->GetPlayerFSM()->isHolding && fsm->GetPlayerFSM()->holdTime < fsm->GetPlayerFSM()->bulletTimeThreshold)
        {
            fsm->GetPlayerFSM()->OnAirAttack();
            fsm->GetPlayerFSM()->GetMovementFSM()->ChangeState(std::make_unique<Attack_State>());
        }

        // �ʱ�ȭ
        fsm->GetPlayerFSM()->isHolding = false; fsm->GetPlayerFSM()->holdTime = 0.0f;
    }


    // [ Idle ] 
    if (fsm->GetPlayerFSM()->GetIsGround())
    {
        fsm->GetPlayerFSM()->GetMovementFSM()->ChangeState(std::make_unique<Idle_State>());
        return;
    }
}

void Hanging_State::FixedUpdate(MovementFSM* fsm)
{
    // �߷��� ���ϰ� ���� (õõ�� ��������)
    fsm->GetPlayerFSM()->GetRigidbody()->gravityScale = 10;
}

void Hanging_State::Exit(MovementFSM* fsm)
{
    fsm->GetPlayerFSM()->GetRigidbody()->gravityScale = 80;

    fsm->GetPlayerFSM()->GetAnimatorController()->SetBool("Hanging", false);
}
