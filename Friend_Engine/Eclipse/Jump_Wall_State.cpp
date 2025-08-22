#include "Jump_Wall_State.h"
#include "Hanging_State.h"
#include "Idle_State.h"
#include "BulletTime_State.h"
#include "Attack_State.h"
#include "Dash_State.h"

#include "MovementFSM.h"
#include "PlayerFSM.h"
#include "PlayerAnimatorController.h"
#include "GameManager.h"

#include "../Direct2D_EngineLib/Rigidbody.h"
#include "../Direct2D_EngineLib/Time.h"
#include "../Direct2D_EngineLib/Input.h"



void Jump_Wall_State::Enter(MovementFSM* fsm)
{
    OutputDebugStringA("[Jump_Wall_State] �� ���� ���� ����\n");
 
    // �ʱ�ȭ 
    fsm->GetPlayerFSM()->holdTime = 0.0f;
    fsm->GetPlayerFSM()->isHolding = false;
    fsm->GetPlayerFSM()->timer = 0.0f;
    fsm->GetPlayerFSM()->OnJump(JumpPhase::WallJump);

    elapsedTime = 0.0f;  // �ð�
    // wallJumpForce = fsm->GetPlayerFSM()->GetJumpForce();
    fsm->GetPlayerFSM()->GetRigidbody()->velocity = Vector2(0, 0); // ���� �ӵ�


    // ù��° Wall Jump ���� 
    if (fsm->GetPlayerFSM()->GetIsWallLeft())
    {
        fsm->GetPlayerFSM()->GetRigidbody()->AddImpulse(Vector2(+jumpXPower, wallJumpForce));  // ������ �������� ƨ��
        lastWallDir = -1;
    }
    else if (fsm->GetPlayerFSM()->GetIsWallRight())
    {
        fsm->GetPlayerFSM()->GetRigidbody()->AddImpulse(Vector2(-jumpXPower, wallJumpForce));  // ���� �������� ƨ��
        lastWallDir = 1;
    }
    else
    {
        lastWallDir = 0;
    }

    // �ִϸ��̼� ���
    fsm->GetPlayerFSM()->GetAnimatorController()->SetBool("Jump", true);

    // ����� 
    fsm->GetPlayerFSM()->GetAudioSource()->SetClip(fsm->GetPlayerFSM()->SFX_Player_Jump);
    fsm->GetPlayerFSM()->GetAudioSource()->PlayOneShot();
}

void Jump_Wall_State::Update(MovementFSM* fsm)
{
    // �ι�° Wall Jump ���� 
    if (GameManager::Get().CheckUnlock(SkillType::DoubleJump) && fsm->GetPlayerFSM()->canDoubleJump && fsm->GetPlayerFSM()->GetIsSpace())
    {
        if (!fsm->GetPlayerFSM()->GetIsGround() && !fsm->GetPlayerFSM()->GetLastFlipX())
        {
            fsm->GetPlayerFSM()->GetRigidbody()->AddImpulse(Vector2(+doubleJumpXPower, wallJumpForce));
        }
        else if (!fsm->GetPlayerFSM()->GetIsGround() && fsm->GetPlayerFSM()->GetLastFlipX())
        {
            fsm->GetPlayerFSM()->GetRigidbody()->AddImpulse(Vector2(-doubleJumpXPower, wallJumpForce));
        }

        fsm->GetPlayerFSM()->OnJump(JumpPhase::DoubleJump);
        fsm->GetPlayerFSM()->canDoubleJump = false;

        // ���� ���� �ִϸ��̼� ����� 
        if (fsm->GetPlayerFSM()->GetPlayerAnimatorController()->GetSkillAvailable())
        {
            fsm->GetPlayerFSM()->GetAnimatorController()->ChangeAnimation(fsm->GetPlayerFSM()->GetPlayerAnimatorController()->jumpState_Y);
        }
        else
        {
            fsm->GetPlayerFSM()->GetAnimatorController()->ChangeAnimation(fsm->GetPlayerFSM()->GetPlayerAnimatorController()->jumpState);
        }

        fsm->GetPlayerFSM()->GetAudioSource()->PlayOneShot();
    }

    // [ Hanging ] 
    // �������� ƨ�� ��, ���� �̵� ���̸�, ���ʺ��� �Ŵ޸��� 
    if (lastWallDir == 1 && fsm->GetPlayerFSM()->GetIsWallLeft() && fsm->GetPlayerFSM()->GetInputX() < -0.5f)
    {
        fsm->ChangeState(std::make_unique<Hanging_State>());
        return;
    }
    else if (lastWallDir == -1 && fsm->GetPlayerFSM()->GetIsWallRight() && fsm->GetPlayerFSM()->GetInputX() > 0.5f)
    {
        fsm->ChangeState(std::make_unique<Hanging_State>());
        return;
    }


    // [ Attack / Bullet ]
    if (fsm->GetPlayerFSM()->CanAttack() && fsm->GetPlayerFSM()->GetIsLButton())
    {
        if (!fsm->GetPlayerFSM()->isHolding) { fsm->GetPlayerFSM()->isHolding = true;   fsm->GetPlayerFSM()->holdTime = 0.0f; }

        fsm->GetPlayerFSM()->holdTime += Time::GetDeltaTime();

        // [ BulletTime ]
        if ( fsm->GetPlayerFSM()->CanAttack() &&
            (fsm->GetPlayerFSM()->holdTime >= fsm->GetPlayerFSM()->bulletTimeThreshold))
        {
            fsm->GetPlayerFSM()->GetMovementFSM()->ChangeState(std::make_unique<BulletTime_State>());
        }
    }
    else
    {
        // [ Attack ]
        if ( fsm->GetPlayerFSM()->CanAttack() &&
            (fsm->GetPlayerFSM()->isHolding && fsm->GetPlayerFSM()->holdTime < fsm->GetPlayerFSM()->bulletTimeThreshold))
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
        fsm->ChangeState(std::make_unique<Idle_State>());
        return;
    }

    // [ Dash ]
    if (fsm->GetPlayerFSM()->GetisShift() && fsm->GetPlayerFSM()->CanDash())
    {
        fsm->ChangeState(std::make_unique<Dash_State>());
        return;
    }
}

void Jump_Wall_State::FixedUpdate(MovementFSM* fsm)
{
    elapsedTime += Time::GetDeltaTime();

    if (elapsedTime < inputBlockTime) return;

    // [ ���� �ϰ� ]
    if (GameManager::Get().CheckUnlock(SkillType::FastFall) &&
        fsm->GetPlayerFSM()->GetRigidbody()->velocity.y < 0 && // �ְ��� ���� ����
        fsm->GetPlayerFSM()->GetIsS())
    {
        fsm->GetPlayerFSM()->GetRigidbody()->gravityScale = fsm->GetPlayerFSM()->fastFallGravity;
    }
    else
    {
        fsm->GetPlayerFSM()->GetRigidbody()->gravityScale = fsm->GetPlayerFSM()->defaultGravity;
    }


    // [ �¿� �̵� ]
    inputX = fsm->GetPlayerFSM()->GetInputX();
    curVelX = fsm->GetPlayerFSM()->GetRigidbody()->velocity.x;

    // �Է��� �ִ� ���: ��ǥ �ӵ��� ���� ()
    if (inputX != 0.0f)
    {
        curVelX = inputX * fsm->GetPlayerFSM()->GetCurSpeed();
        fsm->GetPlayerFSM()->GetRigidbody()->velocity.x = Lerp(curVelX, curVelX, Time::GetDeltaTime() * airAcceleration);
    }
    else
    {
        // �Է� ������ ����
        fsm->GetPlayerFSM()->GetRigidbody()->velocity.x = Lerp(curVelX, 0.0f, Time::GetDeltaTime() * airFriction);
    }
}

void Jump_Wall_State::Exit(MovementFSM* fsm)
{
    fsm->GetPlayerFSM()->GetAnimatorController()->SetBool("Jump", false);
    fsm->GetPlayerFSM()->GetAudioSource()->Stop();
}