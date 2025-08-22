#include "MoonShadowController.h"
#include "../Friend_2D_EngineLib/Time.h"
#include "../Friend_2D_EngineLib/Camera.h"
#include "../Friend_2D_EngineLib/InvokeSystem.h"
#include "GameManager.h"
#include "MoonLight.h"
#include "GameManager.h"
#include "PlayUI.h"


void MoonShadowController::Awake() 
{
	tr = gameObject->transform;
	moonTr = GameObject::Find("Moon")->transform;

	tr->SetScale(0.99, 0.99);
}

void MoonShadowController::Update()
{
	// 1~3 wave
	isWaving = GameManager::Get().isWave;
	if (!isStop && isWaving)
	{
		tr->Translate(Vector2::left * Time::GetDeltaTime() * speed);
	}

	// boss wave ���� �� ����
	if (!isStop && isBossWave)
	{
		tr->Translate(Vector2::left * Time::GetDeltaTime() * speed * 25);

		// ����
		if (tr->GetWorldPosition().x <= moonTr->GetWorldPosition().x)
		{
			isStop = true;
			isDirecting = false;
			tr->SetPosition(moonTr->GetWorldPosition());
			Instantiate<MoonLight>(moonTr->GetWorldPosition());
			
			// boss wave start
			GameManager::Get().g_playUI->BossIntroEnd();

			// affter
			InvokeSystem::Invoke(2, [this]() { AfterMovingStart(); });
		}
	}

	// boss wave
	if (isAfterMoving && isWaving)
	{
		tr->Translate(Vector2::left * Time::GetDeltaTime() * speed * 4);
	}
}

void MoonShadowController::DirectingBossWave()
{
	isBossWave = true;
	isDirecting = true;

	// ����
	Camera::GetMainCamera()->UseTargetTrace(false);
	Camera::GetMainCamera()->gameObject->transform->SetPosition(0, 250);
}


void MoonShadowController::AfterMovingStart()
{
	isAfterMoving = true;
	Camera::GetMainCamera()->UseTargetTrace(true);
}

void MoonShadowController::ReStart()
{
	// restart
	isStop = false;
	isAfterMoving = false;
	tr->SetPosition(moonTr->GetWorldPosition().x + 100, moonTr->GetWorldPosition().y);
}