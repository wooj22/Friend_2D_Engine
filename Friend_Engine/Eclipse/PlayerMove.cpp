#include "PlayerMove.h"
#include "PlayUI.h"
#include "Chat.h"
#include "Quest.h"
#include "../Friend_2D_EngineLib/Time.h"
#include "GameManager.h"

void PlayerMove::OnEnable()
{
	transform = gameObject->transform;
	rigid = gameObject->GetComponent<Rigidbody>();
}

void PlayerMove::Update()
{
	inputX = Input::GetAxisHorizontal();
	inputY = Input::GetAxisVertical();
	if (inputX == 0) rigid->velocity.x = 0; // ���� �̵��� ���� �� �ӵ� �ʱ�ȭ
	if (inputY == 0) rigid->velocity.y = 0; // ���� �̵��� ���� �� �ӵ� �ʱ�ȭ
	rigid->velocity.x += inputX * speed * Time::GetDeltaTime();
	rigid->velocity.y += inputY * speed * Time::GetDeltaTime();

	if (Input::GetKeyDown('F'))
	{
		GameManager::Get().g_playUI->PlayerInteraction();
	}

	if (Input::GetKeyDown(VK_RETURN))
	{
		GameManager::Get().isWave = false;
	}
}
void PlayerMove::OnTriggerStay(ICollider* other, const ContactInfo& contact)
{
	if (other->gameObject->name == "NPC" && !GameManager::Get().g_playUI->ChatActiveCheck() 
		&& !GameManager::Get().isWave && Input::GetKey('F'))
	{
		GameManager::Get().g_playUI->ChatSetActive(true);
	}
}
