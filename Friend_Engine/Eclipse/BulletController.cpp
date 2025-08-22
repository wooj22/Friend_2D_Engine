#include "BulletController.h"
#include "../Friend_2D_EngineLib/GameObject.h"
#include "../Friend_2D_EngineLib/Transform.h"
#include "../Friend_2D_EngineLib/Time.h"
#include "../Friend_2D_EngineLib/Input.h"
#include "../Friend_2D_EngineLib/Vector2.h"
#include "PlayerFSM.h"

void BulletController::Awake()
{
	tr = this->gameObject->transform;
}

void BulletController::Start()
{

}

void BulletController::Update()
{
	tr->Translate(direction * speed * Time::GetDeltaTime());
}

void BulletController::OnDestroy()
{

}

void BulletController::OnTriggerEnter(ICollider* other, const ContactInfo& contact)
{
	if (other->gameObject->name == "Player")
	{
		other->gameObject->GetComponent<PlayerFSM>()->SetSpeedDownRate(palyer_deceleration);
		this->gameObject->Destroy();
	}
}