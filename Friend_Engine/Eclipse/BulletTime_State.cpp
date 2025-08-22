#include "BulletTime_State.h"
#include "Attack_State.h"
#include "Fall_State.h"
#include "MovementFSM.h"
#include "PlayerFSM.h"
#include "PlayerAnimatorController.h"
#include "AfterImage.h"

#include "../Friend_2D_EngineLib/Time.h"
#include "../Friend_2D_EngineLib/Input.h"
#include "../Friend_2D_EngineLib/RenderSystem.h"
#include "../Friend_2D_EngineLib/Vector2.h"
#include "../Friend_2D_EngineLib/Camera.h"



void BulletTime_State::Enter(MovementFSM* fsm)
{
    OutputDebugStringA("[BulletTime_State] (( ���� - �Ҹ� Ÿ�� ���� )) \n");
    Time::SetTimeScale(0.3f); // �ð� ������

    fsm->GetPlayerFSM()->timer = 0.0f;

    blackOut_renderer = GameObject::Find("BlackOut")->GetComponent<SpriteRenderer>();
    blackOut_renderer->SetEnabled(true);
}

void BulletTime_State::Update(MovementFSM* fsm)
{
    float delta = Time::GetDeltaTime();
    float unscaledDelta = delta / Time::GetTimeScale();  // timeScale ������ ���� �ð� ���

    fsm->GetPlayerFSM()->timer += unscaledDelta;

    // [ Attack ] ���콺 ���� ��ư���� ���� ���� �� -> ����
    if (fsm->GetPlayerFSM()->GetIsLButtonUp())
    {
        Time::SetTimeScale(1.0f); 
        fsm->GetPlayerFSM()->OnAirAttack();
        fsm->GetPlayerFSM()->isBulletAttack = true; 
        fsm->ChangeState(std::make_unique<Attack_State>());
        return;
    }

    // [ Idle ] ���� ��� 
    if (fsm->GetPlayerFSM()->GetIsRButton())
    { 
        // ���� ���콺 ���� ������ �־����� ���û���  
        if (fsm->GetPlayerFSM()->GetIsLButton()) fsm->GetPlayerFSM()->isAttackIgnore = true;

        if (fsm->GetPlayerFSM()->GetIsGround()) { fsm->ChangeState(std::make_unique<Idle_State>()); return; }
        else
        {
            fsm->ChangeState(std::make_unique<Fall_State>()); return;
        }
    }

    // [ Idle ] �Ҹ� Ÿ�� �� 
    if (fsm->GetPlayerFSM()->timer >= fsm->GetPlayerFSM()->bulletTimeDuration)
    {
        Time::SetTimeScale(1.0f); // �ð� ����

        // ���� ���콺 ���� ������ �־����� ���û���  
        if (fsm->GetPlayerFSM()->GetIsLButton()) fsm->GetPlayerFSM()->isAttackIgnore = true;

        if (fsm->GetPlayerFSM()->GetIsGround()) { fsm->ChangeState(std::make_unique<Idle_State>()); return; }
        else
        {
            fsm->ChangeState(std::make_unique<Fall_State>()); return;
        }
    }


    // [ ���콺 ���� ���� FlipX ]
    fsm->GetPlayerFSM()->SetisBulletFliping(true);

    Vector2 playerPos = fsm->GetPlayerFSM()->GetTransform()->GetPosition();
    Vector2 mousePos = fsm->GetPlayerFSM()->MouseWorldPos;

    //if (mousePos.x < playerPos.x) fsm->GetPlayerFSM()->SetisBulletFlipX(true);  // ����
    //else fsm->GetPlayerFSM()->SetisBulletFlipX(false);

    if (mousePos.x < playerPos.x) fsm->GetPlayerFSM()->SetisBulletFlipX(false);  
    else fsm->GetPlayerFSM()->SetisBulletFlipX(true);



    // ----- [ �÷��̾�-���콺 ��ġ ����� �� �׸��� ] : ��ü �Ÿ� ----- 
    // 
    //D2D1_POINT_2F start = { playerPos.x, playerPos.y };     // �÷��̾� ���� ��ġ 
    //D2D1_POINT_2F end = { mousePos.x,  mousePos.y };        // ���콺 ���� ��ġ -> ���� �̵��ϴ� �Ÿ� ��ŭ 

    //// ���� -> ��ũ�� ��ȯ�� 
    //const auto& screenMatrix 
    //    = Transform::renderMatrix * Camera::GetMainInverseMatrix() * Transform::unityMatrix;

    //// ����� �� �׸���
    //RenderSystem::Get().DebugDrawLine(start, end, screenMatrix, 2.0f);


    // ----- [ �÷��̾�-���콺 ��ġ ����� �� �׸��� ] : ���� �̵��ϴ� �Ÿ� -----
    // 
    float baseMaxDist = fsm->GetPlayerFSM()->maxAttackDistance;
    float bonus = fsm->GetPlayerFSM()->GetAttackRangeBonus(); // �ر� ������ ���� �Ÿ� ���� 
    float maxDistance = baseMaxDist * bonus;

    Vector2 toMouse = mousePos - playerPos;
    Vector2 direction = toMouse.Normalized();
    float actualDistance = ((toMouse.Magnitude()) < (maxDistance)) ? (toMouse.Magnitude()) : (maxDistance);

    Vector2 limitedTargetPos = playerPos + direction * actualDistance;

    D2D1_POINT_2F start = { playerPos.x, playerPos.y };
    D2D1_POINT_2F end = { limitedTargetPos.x, limitedTargetPos.y };

    // ���� �� ��ũ�� ��ȯ
    const auto& screenMatrix = Transform::renderMatrix * Camera::GetMainInverseMatrix() * Transform::unityMatrix;
    
    // ����� �� �׸���
    RenderSystem::Get().DebugDrawLine(start, end, screenMatrix, 2.0f);

    // �ܻ� 
    afterimageTimer += unscaledDelta;
    if (afterimageTimer >= afterimageInterval)
    {
        afterimageTimer = 0.0f;

        CreateAfterImage(fsm);
    }

    if (GameManager::Get().isQuest && GameManager::Get().questIndex == 2)
        GameManager::Get().CheckQuest(2, 1);
}

void BulletTime_State::FixedUpdate(MovementFSM* fsm)
{

}

void BulletTime_State::Exit(MovementFSM* fsm)
{
    OutputDebugStringA("[BulletTime_State] (( ���� - �Ҹ� Ÿ�� �� )) \n");

    // ���� 
    Time::SetTimeScale(1.0f);
    fsm->GetPlayerFSM()->SetisBulletFliping(false);

    blackOut_renderer->SetEnabled(false);
}

void BulletTime_State::CreateAfterImage(MovementFSM* fsm)
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