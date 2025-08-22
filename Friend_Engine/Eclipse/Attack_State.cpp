#include "Attack_State.h"
#include "Idle_State.h"
#include "MovementFSM.h" 
#include "PlayerFSM.h" 
#include "PlayerAnimatorController.h"

#include "../Friend_2D_EngineLib/Time.h"
#include "../Friend_2D_EngineLib/BoxCollider.h"
#include "../Friend_2D_EngineLib/Rigidbody.h"
#include "../Friend_2D_EngineLib/Vector2.h"

#include "Fall_State.h"
#include "AfterImage.h"

void Attack_State::Enter(MovementFSM* fsm)
{
    OutputDebugStringA("[Attack_State] Player�� Attack_State ���� \n");

    fsm->GetPlayerFSM()->GetRigidbody()->useGravity = false;
    fsm->GetPlayerFSM()->GetRigidbody()->velocity = Vector2::zero;

    // �ʱ�ȭ : ��ų �ر� ������ ���� ����
    float skillBonus = fsm->GetPlayerFSM()->GetAttackRangeBonus();
    baseMaxDistance = fsm->GetPlayerFSM()->maxAttackDistance * skillBonus;
    desiredTime = fsm->GetPlayerFSM()->attackDesiredTime;

    // �ִϸ��̼� ��� 
    fsm->GetPlayerFSM()->GetAnimatorController()->SetBool("Attack", true);

    startPos = fsm->GetPlayerFSM()->GetTransform()->GetPosition();   // ���� ��ġ 
    Vector2 toMouse = fsm->GetPlayerFSM()->MouseWorldPos - startPos; // ��ǥ ��ġ 

    // �̵� �Ÿ� ���� (���콺���� �ָ� �� ��)
    float actualDistance = (toMouse.Magnitude() < baseMaxDistance) ? toMouse.Magnitude() : baseMaxDistance;
    direction = toMouse.Normalized();

    // [ ���� �̵� ���� ]
    airAttack = !fsm->GetPlayerFSM()->GetIsGround() || (fsm->GetPlayerFSM()->isBulletAttack && fsm->GetPlayerFSM()->MouseWorldPos.y > startPos.y);

    if (airAttack)
    {
        targetPos = startPos + direction * actualDistance;
        moveSpeed = actualDistance / desiredTime; // �ӵ� ��� : �Ÿ� / �ð�
        fsm->GetPlayerFSM()->GetRigidbody()->AddImpulse(Vector2(0, 5.0f));
        OutputDebugStringA("[Attack_State] ���� ���� ���� \n");
    }
    else
    {
        // ������ ���ڸ� ����
        targetPos = startPos;
        targetPos = toMouse.Normalized();
        moveSpeed = 0.0f;
        OutputDebugStringA("[Attack_State] ���ڸ� ���� ���� \n");
    }


    // ���� ���� ���� 
    fsm->GetPlayerFSM()->attackDirection = direction;

    // �¿� ���� ó��
    if (direction.x < 0) fsm->GetPlayerFSM()->SetLastFlipX(false);
    else if (direction.x > 0) fsm->GetPlayerFSM()->SetLastFlipX(true);


    // [ ����Ʈ, �浹 ]

    // ���� ��� 
    float angleRad = atan2(direction.y, direction.x);
    float angleDeg = angleRad * (180.0f / 3.14159265f);

    // PlayerAttackArea �ݶ��̴� ��ġ/ȸ�� ����
    attackAreaPosition = startPos + direction * attackAreaDistance;
    fsm->GetPlayerFSM()->GetPlayerAttackArea()->GetComponent<Transform>()->SetPosition(attackAreaPosition);
	fsm->GetPlayerFSM()->GetPlayerAttackArea()->GetComponent<Transform>()->SetRotation(angleDeg + 180.0f); // -90�� ȸ�� ����
   
    // ���� ����Ʈ �ִϸ��̼� 
    auto anim = fsm->GetPlayerFSM()->GetPlayerAttackArea()->GetComponent<Animator>();
    if (anim)
    {
        auto attackAnimCtrl = dynamic_cast<AttackAnimatorController*>(anim->controller);
        if (attackAnimCtrl)
        {
            attackAnimCtrl->PlayAttack();
        }
    }

    // ����Ʈ & ���� Ȱ��ȭ
    fsm->GetPlayerFSM()->GetPlayerAttackArea()->Activate();

    // ����� 
    fsm->GetPlayerFSM()->GetAudioSource()->SetClip(fsm->GetPlayerFSM()->SFX_Player_Attack);
    fsm->GetPlayerFSM()->GetAudioSource()->PlayOneShot();

    if (GameManager::Get().isQuest && GameManager::Get().questIndex == 2)
        GameManager::Get().CheckQuest(2, 0);
}

void Attack_State::Update(MovementFSM* fsm)
{
    timer += Time::GetDeltaTime();
}

void Attack_State::FixedUpdate(MovementFSM* fsm) 
{
    if (!fsm->GetPlayerFSM()->GetRigidbody() || !fsm->GetPlayerFSM()->GetTransform()) return;

    // ���� ���� ��ġ ����
    Vector2 playerPos = fsm->GetPlayerFSM()->GetTransform()->GetPosition();
    Vector2 toMouse = fsm->GetPlayerFSM()->MouseWorldPos - playerPos;

    if (toMouse.Magnitude() > 0.001f) // 0������ ����
    {
        Vector2 direction = toMouse.Normalized();
        Vector2 attackAreaPos = playerPos + direction * attackAreaDistance;

        // ���� ���� ��ġ ����
        fsm->GetPlayerFSM()->GetPlayerAttackArea()->GetComponent<Transform>()->SetPosition(attackAreaPos);
		// ���� ���� ȸ�� ����
		float angleRad = atan2(direction.y, direction.x);
		float angleDeg = angleRad * (180.0f / 3.14159265f);
		fsm->GetPlayerFSM()->GetPlayerAttackArea()->GetComponent<Transform>()->SetRotation(angleDeg + 180.0f); // -90�� ȸ�� ����
    }

    // �ܻ� 
    if (airAttack)
    {
        afterimageTimer += Time::GetDeltaTime();
        if (afterimageTimer >= afterimageInterval)
        {
            afterimageTimer = 0.0f;

            CreateAfterImage(fsm);
        }
    }

    if (!isAttackStart)
    {
       fsm->GetPlayerFSM()->GetRigidbody()->velocity = direction * moveSpeed; // �̵�
    }

    if (timer >= desiredTime)
    {
        if (fsm->GetPlayerFSM()->GetIsGround()) { fsm->GetPlayerFSM()->GetMovementFSM()->ChangeState(std::make_unique<Idle_State>()); return; }
        else { fsm->GetPlayerFSM()->GetMovementFSM()->ChangeState(std::make_unique<Fall_State>()); return; }
    }

    // if (direction == Vector2::zero) return;

    Vector2 currentPos = fsm->GetPlayerFSM()->GetTransform()->GetPosition();
    float traveled = (currentPos - startPos).Magnitude(); 
    float totalDistance = (targetPos - startPos).Magnitude(); 

    // ���� ���� ����
    if (traveled >= totalDistance)
    {
        fsm->GetPlayerFSM()->GetMovementFSM()->ChangeState(std::make_unique<Fall_State>());
        return;
    }
    else if (fsm->GetPlayerFSM()->GetIsGround() || fsm->GetPlayerFSM()->GetIsWallLeft() || fsm->GetPlayerFSM()->GetIsWallRight())
    {
        // �������� ���ߴµ�, �� or �� �̶� �浹���� �� 
        fsm->GetPlayerFSM()->GetRigidbody()->useGravity = false;
        fsm->GetPlayerFSM()->GetRigidbody()->velocity.y = 0;
        fsm->GetPlayerFSM()->GetRigidbody()->useGravity = true;
    }
}

void Attack_State::Exit(MovementFSM* fsm)
{
    fsm->GetPlayerFSM()->OnAirAttack();
    fsm->GetPlayerFSM()->isBulletAttack = false;

    fsm->GetPlayerFSM()->GetRigidbody()->useGravity = true;
    fsm->GetPlayerFSM()->GetRigidbody()->velocity.y = 0;

    fsm->GetPlayerFSM()->GetPlayerAttackArea()->Deactivate();

    fsm->GetPlayerFSM()->GetAnimatorController()->SetBool("Attack", false);

    fsm->GetPlayerFSM()->GetAudioSource()->Stop();
}


void Attack_State::CreateAfterImage(MovementFSM* fsm)
{
    PlayerFSM* player = fsm->GetPlayerFSM();
    if (!player) return;

    // ���� ��������Ʈ ��������
    SpriteRenderer* playerRenderer = player->GetSpriteRenderer();
    if (!playerRenderer) return;

    shared_ptr<Sprite> currentSprite = playerRenderer->sprite;
    if (!currentSprite || !currentSprite->texture || !currentSprite->texture->texture2D)
    {
        OutputDebugStringA("AfterImage sprite�� texture�� ����!\n");
        return;
    }

    // ��ġ �� ����
    Vector2 position = player->GetTransform()->GetPosition();
    bool flipX = playerRenderer->flipX;

    // �ܻ� ������Ʈ ���� 
    GameObject* afterImage = player->Instantiate<GameObject>();
    afterImage->AddComponent<Transform>()->SetScale(player->GetTransform()->GetScale());
    afterImage->GetComponent<Transform>()->SetPosition(position);

    // ������ �߰�
    auto renderer = afterImage->AddComponent<SpriteRenderer>();
    renderer->sprite = currentSprite;
    renderer->flipX = flipX;
    renderer->flipY = playerRenderer->flipY;
    renderer->SetAlpha(0.1f);
    renderer->SetColor(1.0f, 1.0f, 0.8f);
    renderer->renderMode = RenderMode::Lit_ColorTint;
    renderer->layer = 1;

    // �ܻ� ��ũ��Ʈ
    auto afterImageScript = afterImage->AddComponent<AfterImage>();
    afterImageScript->SetInitialAlpha(0.4f);
}