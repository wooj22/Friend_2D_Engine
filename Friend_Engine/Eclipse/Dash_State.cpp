#include "Dash_State.h"
#include "Idle_State.h"
#include "MovementFSM.h"
#include "PlayerFSM.h"
#include "Fall_State.h"
#include "PlayerAnimatorController.h"

#include "../Direct2D_EngineLib/Rigidbody.h"
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/Time.h"
#include "AfterImage.h"
#include "JumpAnimatorController.h"


void Dash_State::Enter(MovementFSM* fsm)
{
    OutputDebugStringA("[Dash_State] Dash ����\n");

    dashTimer = 0.0f;

    // ���� ó��
    fsm->GetPlayerFSM()->SetInvincible(true);

    // ���� �ʱ�ȭ 
    fsm->GetPlayerFSM()->GetRigidbody()->velocity = Vector2(0, 0);
    fsm->GetPlayerFSM()->GetRigidbody()->useGravity = false;
    
    // ��� 
    moveBonus = fsm->GetPlayerFSM()->GetMoveSpeedBonus();
    dashSpeed = (fsm->GetPlayerFSM()->GetWalkSpeed() + moveBonus) * 4.0f; 

    inputX = fsm->GetPlayerFSM()->GetInputX();

    // �Է��� ���� ��� �ٶ󺸴� �������� ����
    if (inputX == 0)
    {
        bool flipX = fsm->GetPlayerFSM()->GetLastFlipX();
        inputX = flipX ? 1 : -1;  
    }

    // ���� ��ġ �������� ���� riseAmount ��ŭ ���
    Vector2 currentPos = fsm->GetPlayerFSM()->GetTransform()->GetPosition();
    targetYPosition = currentPos.y - riseAmount; // Y�� ���� ������ ����� -riseAmount

    Vector2 newPos = Vector2(currentPos.x, targetYPosition);
    fsm->GetPlayerFSM()->GetTransform()->SetPosition(newPos);

    // �ִϸ��̼�
    fsm->GetPlayerFSM()->GetAnimatorController()->SetBool("Dash", true);


    // [ ��� ����Ʈ ��� (�¿����) ]
    auto jumpEffect = GameObject::Find("PlayerJumpEffect");
    auto jump_tr = jumpEffect->GetComponent<Transform>();
    auto jump_renderer = jumpEffect->GetComponent<SpriteRenderer>();

    bool facingRight = fsm->GetPlayerFSM()->GetLastFlipX();
    jump_renderer->flipX = facingRight;

    Vector2 offset = facingRight ? Vector2(-30, -90) : Vector2(30, -90);
    jump_tr->SetPosition(fsm->GetPlayerFSM()->GetTransform()->GetWorldPosition() + offset);

    auto anim = GameObject::Find("PlayerJumpEffect")->GetComponent<Animator>();
    if (anim)
    {
        auto jumpAnimCtrl = dynamic_cast<JumpAnimatorController*>(anim->controller);
        if (jumpAnimCtrl)
        {
            jumpAnimCtrl->PlayJump();
        }
    }

    // ����� 
    fsm->GetPlayerFSM()->GetAudioSource()->SetClip(fsm->GetPlayerFSM()->SFX_Player_Dash);
    fsm->GetPlayerFSM()->GetAudioSource()->PlayOneShot();

    fsm->GetPlayerFSM()->ResetDashCooldown();

    if(GameManager::Get().isQuest && GameManager::Get().questIndex == 2)
        GameManager::Get().CheckQuest(2, 2);
}

void Dash_State::Update(MovementFSM* fsm)
{
    dashTimer += Time::GetDeltaTime();

    if (dashTimer >= dashDuration)
    {
        // ���� ����
        fsm->GetPlayerFSM()->SetInvincible(false);  

        // ���� ��ȯ
        if (fsm->GetPlayerFSM()->GetIsGround()) fsm->ChangeState(std::make_unique<Idle_State>());
        else fsm->ChangeState(std::make_unique<Fall_State>());

        return;
    }

    // Jump ����Ʈ fsm->GetPlayerFSM()->GetLastFlipX() �� ���� x�� �̵�
    auto jumpEffect = GameObject::Find("PlayerJumpEffect");
    if (!jumpEffect) return;

    auto jump_tr = jumpEffect->GetComponent<Transform>();
    if (!jump_tr) return;

    // ���� Ȯ��
    bool facingRight = fsm->GetPlayerFSM()->GetLastFlipX();
    float moveSpeed = 100.0f;

    // deltaTime ���ؼ� ������ ������ �̵�
    float moveX = (facingRight ? -1.0f : 1.0f) * moveSpeed * Time::GetDeltaTime();

    jump_tr->Translate(moveX, 0.0f);
}

void Dash_State::FixedUpdate(MovementFSM* fsm)
{
    // X�� �ӵ��� ���� (Y�� ����)
    fsm->GetPlayerFSM()->GetRigidbody()->velocity = Vector2(inputX * dashSpeed, 0.0f);

    // Y��ġ ����
    Vector2 currentPos = fsm->GetPlayerFSM()->GetTransform()->GetPosition();
    currentPos.y = targetYPosition;
    fsm->GetPlayerFSM()->GetTransform()->SetPosition(currentPos);

    //std::string debugStr = "[Dash_State] velocity.y = " + std::to_string(fsm->GetPlayerFSM()->GetRigidbody()->velocity.y) + "\n";
    //OutputDebugStringA(debugStr.c_str());

    afterimageTimer += Time::GetDeltaTime();
    if (afterimageTimer >= afterimageInterval)
    {
        afterimageTimer = 0.0f;

        CreateAfterImage(fsm);
    }
}

void Dash_State::Exit(MovementFSM* fsm)
{
    OutputDebugStringA("[Dash_State] Dash ����\n");

    // ���� �ʱ�ȭ 
    fsm->GetPlayerFSM()->GetRigidbody()->velocity = Vector2(0, 0);
    fsm->GetPlayerFSM()->GetRigidbody()->useGravity = true;

    // ��� �� ��Ÿ�� ����
    fsm->GetPlayerFSM()->ResetDashCooldown(); 

    // �ִϸ��̼� ����
    fsm->GetPlayerFSM()->GetAnimatorController()->SetBool("Dash", false);

    fsm->GetPlayerFSM()->GetAudioSource()->Stop();

    // NormalJump �÷��׸� �����ϵ��� ����
    auto& attacks = fsm->GetPlayerFSM()->canAttackAfterJump;
    attacks[JumpPhase::NormalJump] = true;
    attacks[JumpPhase::DoubleJump] = true;
    attacks[JumpPhase::WallJump] = true;
}


void Dash_State::CreateAfterImage(MovementFSM* fsm)
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
