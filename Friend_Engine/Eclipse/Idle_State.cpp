#include "Idle_State.h"
#include "Walk_State.h"
#include "Jump_State.h"
#include "Attack_State.h"
#include "BulletTime_State.h"
#include "Fall_State.h"
#include "Dash_State.h"

#include "MovementFSM.h" 
#include "PlayerFSM.h"
#include "PlayerAnimatorController.h"

#include "../Friend_2D_EngineLib/Rigidbody.h"
#include "../Friend_2D_EngineLib/Time.h"
#include "../Friend_2D_EngineLib/Input.h"


void Idle_State::Enter(MovementFSM* fsm)
{
    OutputDebugStringA("[Idle_State] Player�� Idle_State ���� \n");

    // �ʱ�ȭ 
    fsm->GetPlayerFSM()->timer = 0.0f;
    fsm->GetPlayerFSM()->holdTime = 0.0f;
    fsm->GetPlayerFSM()->isHolding = false;

    fsm->GetPlayerFSM()->OnGround();  // ��� ���� ��ȸ ����

    fsm->GetPlayerFSM()->GetRigidbody()->velocity = Vector2(0, 0);  // �������� �־��ٸ� ���� 

    // �ִϸ��̼� ���
    fsm->GetPlayerFSM()->GetAnimatorController()->SetBool("Idle", true);

    // ����� 
    // fsm->GetPlayerFSM()->GetAudioSource()->SetClip(fsm->GetPlayerFSM()->SFX_Player_Land);
    // fsm->GetPlayerFSM()->GetAudioSource()->PlayOneShot();
}

void Idle_State::Update(MovementFSM* fsm)
{
    fsm->GetPlayerFSM()->timer += Time::GetDeltaTime();

    // ���� �Է� ���� 
    if(fsm->GetPlayerFSM()->isAttackIgnore && fsm->GetPlayerFSM()->timer > 0.3f) fsm->GetPlayerFSM()->isAttackIgnore = false;

    // DubleJump / Hanging �ʱ�ȭ
    if (fsm->GetPlayerFSM()->GetIsGround())
    {
        fsm->GetPlayerFSM()->canDoubleJump = true;
        fsm->GetPlayerFSM()->canHanging = true;
        fsm->GetPlayerFSM()->canFallAttack = true;
    }

    // [ Jump ]
    if (fsm->GetPlayerFSM()->GetIsSpace() && fsm->GetPlayerFSM()->GetIsGround())
    {
        fsm->GetPlayerFSM()->OnJump(JumpPhase::NormalJump);
        fsm->GetPlayerFSM()->GetMovementFSM()->ChangeState(std::make_unique<Jump_State>());
    }

    // [ Walk ]
    if (fsm->GetPlayerFSM()->GetIsA() || fsm->GetPlayerFSM()->GetIsD())
    {
        fsm->GetPlayerFSM()->GetMovementFSM()->ChangeState(std::make_unique<Walk_State>());
    }

    // [ Attack / BulletTime ]
    if (!fsm->GetPlayerFSM()->isAttackIgnore && fsm->GetPlayerFSM()->GetIsGround())
    {
        // ��ư ���� ���� -> Ȧ�� ����
        if (fsm->GetPlayerFSM()->GetIsLButtonDown())
        {
            fsm->GetPlayerFSM()->isHolding = true;
            fsm->GetPlayerFSM()->holdTime = 0.0f;
        }

        // Ȧ�� ���̸� �ð� ����
        if (fsm->GetPlayerFSM()->isHolding && fsm->GetPlayerFSM()->GetIsLButton())
        {
            fsm->GetPlayerFSM()->holdTime += Time::GetDeltaTime();

            // ��� �������� BulletTime
            if (fsm->GetPlayerFSM()->holdTime >= fsm->GetPlayerFSM()->bulletTimeThreshold)
            {
                fsm->GetPlayerFSM()->GetMovementFSM()->ChangeState(std::make_unique<BulletTime_State>());
                return;
            }
        }

        // ��ư �� ���� -> Ȧ�� ª���� Attack, ��� �̹� BulletTime���� �������� 
        if (fsm->GetPlayerFSM()->GetIsLButtonUp() && fsm->GetPlayerFSM()->isHolding)
        {
            if (fsm->GetPlayerFSM()->holdTime < fsm->GetPlayerFSM()->bulletTimeThreshold)
            {
                fsm->GetPlayerFSM()->GetMovementFSM()->ChangeState(std::make_unique<Attack_State>());
                return;
            }
            fsm->GetPlayerFSM()->isHolding = false;
            fsm->GetPlayerFSM()->holdTime = 0.0f;
        }
    }
    else
    {
        // UI ���� ������ �Է� ��ȿȭ �� Ȧ�� �ʱ�ȭ
        fsm->GetPlayerFSM()->isHolding = false;
        fsm->GetPlayerFSM()->holdTime = 0.0f;
    }


    // [ Fall ]
    if (!fsm->GetPlayerFSM()->GetIsGround())
    {
        fsm->GetPlayerFSM()->GetMovementFSM()->ChangeState(std::make_unique<Fall_State>());
    }

    // [ Dash ]
    if (fsm->GetPlayerFSM()->GetisShift() && fsm->GetPlayerFSM()->CanDash())
    {
        fsm->ChangeState(std::make_unique<Dash_State>());
        return;
    }
}


void Idle_State::FixedUpdate(MovementFSM* fsm) {}


void Idle_State::Exit(MovementFSM* fsm)
{
   fsm->GetPlayerFSM()->GetAnimatorController()->SetBool("Idle", false);
}