#include "PlayerAreaController.h"
#include "HonController.h"
#include "PlayerFSM.h"

#include "../Friend_2D_EngineLib/CircleCollider.h"

void PlayerAreaController::Awake()
{
	playerFSM = GameObject::Find("Player")->GetComponent<PlayerFSM>();	
}

void PlayerAreaController::Start()
{

}

void PlayerAreaController::Update()
{

}

void PlayerAreaController::OnDestroy()
{

}


void PlayerAreaController::OnTriggerEnter(ICollider* other, const ContactInfo& contact) 
{
	//std::string debugStr = "[PlayerAreaController] OnTriggerEnter: " + other->gameObject->name + "�� Trigger�浹" + "\n";
 //   OutputDebugStringA(debugStr.c_str());

	if (other->gameObject->tag == "Hon")
	{
		other->gameObject->GetComponent<HonController>()->TakeDamageByPlayer(playerFSM->attackDirection);
		OutputDebugStringA("Hon�� ���� �� \n");
	}
}

void PlayerAreaController::OnTriggerStay(ICollider* other, const ContactInfo& contact)
{
	//std::string debugStr = "[PlayerAreaController] OnTriggerStay: " + other->gameObject->name + "�� Trigger�浹" + "\n";
	//OutputDebugStringA(debugStr.c_str());

	//if (other->gameObject->tag == "Hon")
	//{
	//	other->gameObject->GetComponent<HonController>()->TakeDamageByPlayer(playerFSM->attackDirection);
	//	OutputDebugStringA("Hon�� ���� �� \n");
	//}
}


