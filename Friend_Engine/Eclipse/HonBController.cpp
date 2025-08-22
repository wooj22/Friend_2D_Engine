#include "HonBController.h"
#include "HonB.h"
#include "HonAController.h"
#include "BossController.h"

/*------------- Cycle  -------------*/
void HonBController::Awake()
{
	tr = gameObject->transform;
	sr = gameObject->GetComponent<SpriteRenderer>();
	collider = gameObject->GetComponent<CircleCollider>();
	audioSource = gameObject->GetComponent<AudioSource>();
	playerTr = GameObject::Find("Player")->GetComponent<Transform>();

	sr->renderMode = RenderMode::Lit_ColorTint;
	sr->SetGlowAmmount(10);
}

void HonBController::Start()
{
	tr->SetScale(size, size);
}

void HonBController::Update()
{
	// sound delay destroy
	if (destroyPending)
	{
		if (!audioSource->IsPlaying()) gameObject->Destroy();
		else
		{
			// opacity ����
			OpacityDirecting();
			return;
		}
	}

	// moving
	if (isAbsorption) return;

	if (isPullMoving)
	{
		// pulling move
		pullMovingDelta += Time::GetDeltaTime();
		tr->Translate(pullDirection * collisionSpeed * 1.2f * Time::GetDeltaTime());

		// end pulling
		if (pullMovingDelta >= pullMovingTime) {
			isPullMoving = false;
			pullMovingDelta = 0;

			isCollisionMoving = false;
			collisionMovingDelta = 0;
		}
	}
	else if (isCollisionMoving)
	{
		// collision move
		collisionMovingDelta += Time::GetDeltaTime();
		tr->Translate(moveDirection * collisionSpeed * Time::GetDeltaTime());

		// end collidion moving
		if (collisionMovingDelta >= collisionMovingTime)
		{
			isCollisionMoving = false;
			collisionMovingDelta = 0;
		}
	}
	else
	{
		// descent move
		tr->Translate(descentDirection * descentSpeed * Time::GetDeltaTime());
	}

	// opacity ����
	OpacityDirecting();
}

void HonBController::OnDestroy()
{

}


/*------------- Trigger Event -------------*/
void HonBController::OnTriggerEnter(ICollider* other, const ContactInfo& contact)
{
	// [player collision]
	if (other->gameObject->name == "Player")
	{
		MovementFSM* playerFSM = other->gameObject->GetComponent<PlayerFSM>()->GetMovementFSM();
		if (!playerFSM->IsInState<Attack_State>())
		{
			other->gameObject->GetComponent<PlayerFSM>()->SetSpeedDownRate(palyer_deceleration);
		}
	}

	// [endline collision]
	if (other->gameObject->tag == "EndLine")
	{
		// score
		GameManager::Get().ChangeHonCount(-10);
		gameObject->Destroy();
	}

	// [mapborder collision]
	if (other->gameObject->name == "MapBorder")
	{
		CollisionStart();
		moveDirection = contact.normal;
	}

	// [boss collision]
	if (other->gameObject->tag == "Boss")
	{
		Instantiate<BossHitEffect>(tr->GetWorldPosition());
		other->gameObject->GetComponent<BossController>()->TakeDamage(1);
		gameObject->Destroy();
	}

	// [hon collision]
	if (other->gameObject->tag == "Hon")
	{
		if (gameObject->IsDestroyed() || destroyPending) return;

		// other
		GameObject* otherGameObject = other->gameObject;
		if (otherGameObject->IsDestroyed()) return;
		HonController* otherController = otherGameObject->GetComponent<HonController>();
		if (otherController->destroyPending) return;
		HonType honType = otherController->honType;

		// collision acttion
		switch (honType)
		{
		case HonType::B :		// ���� ���� B-B
		{
			// hp check
			TakeDamage(1);
			otherController->TakeDamage(1);
			if (destroyPending || otherController->destroyPending) return;

			// wave2 quest
			GameManager::Get().ChangeQuestCount(2);

			// collision move start
			// bb �ı�
			if(isb && otherController->isb)
			{
				otherController->TakeDamage(2);
				TakeDamage(2);
			}
			// Bb 2 �п�
			else if (isb || otherController->isb)
			{
				// position
				std::vector<Vector2> offsets = {
					Vector2(-60, 60),
					Vector2(60, -60),
				};

				if (isb)
				{
					// new HonB
					for (const Vector2& offset : offsets)
					{
						GameObject* newHonB = Instantiate<HonB>(other->gameObject->transform->GetWorldPosition() + offset);
						HonBController* controller = newHonB->GetComponent<HonBController>();
						if (controller)
						{
							controller->SetSize(size * 0.7f);
							controller->SetDescentSpeed(descentSpeed * 1.2f);
							controller->SetHp(2);
							controller->isb = true;
						}
					}

					// sound
					audioSource->SetClip(SFX_HonSplit);
					audioSource->PlayOneShot();

					// ���ϱ� �׳� �ı�
					other->gameObject->Destroy();
				}
				else
				{
					// new HonB
					for (const Vector2& offset : offsets)
					{
						GameObject* newHonB = Instantiate<HonB>(tr->GetWorldPosition() + offset);
						HonBController* controller = newHonB->GetComponent<HonBController>();
						if (controller)
						{
							controller->SetSize(size * 0.7f);
							controller->SetDescentSpeed(descentSpeed * 1.2f);
							controller->SetHp(2);
							controller->isb = true;
						}
					}

					sr->SetEnabled(false);
					collider->SetEnabled(false);

					// sound
					audioSource->SetClip(SFX_HonSplit);
					audioSource->PlayOneShot();

					// sound dealy
					// old HonB
					destroyPending = true;
				}
			}
			// BB 4 �п�
			else
			{
				// position
				std::vector<Vector2> offsets = {
					Vector2(-100, 100),
					Vector2(-100, -100),
					Vector2(100, -100),
					Vector2(100, 100)
				};

				// new HonB
				for (const Vector2& offset : offsets)
				{
					GameObject* newHonB = Instantiate<HonB>(tr->GetWorldPosition() + offset);
					HonBController* controller = newHonB->GetComponent<HonBController>();
					if (controller)
					{
						controller->SetSize(size * 0.7f);
						controller->SetDescentSpeed(descentSpeed * 1.2f);
						controller->SetHp(2);
						controller->isb = true;
					}
				}

				sr->SetEnabled(false);
				collider->SetEnabled(false);
				otherController->sr->SetEnabled(false);
				otherController->collider->SetEnabled(false);

				// sound
				audioSource->SetClip(SFX_HonSplit);
				audioSource->PlayOneShot();

				// sound dealy
				// old HonB
				otherController->destroyPending = true;
				destroyPending = true;
			}
		}
		case HonType::C:		// ���� ���� B-C (C�ʿ��� ó���ؼ� �ڱ� ������ ���)
		{
			honBC_dir = other->gameObject->transform->GetWorldPosition() - tr->GetWorldPosition();
		}
		}
	}
}

// Hon B-C ��ħ �Ұ�
void HonBController::OnTriggerStay(ICollider* other, const ContactInfo& contact)
{
	if (other->gameObject->name == "HonC")
	{
		honBC_dir = honBC_dir.Normalized();
		tr->Translate(honBC_dir * collisionSpeed * 1.3 * Time::GetDeltaTime());
	}
}


// Player Attack
void HonBController::TakeDamageByPlayer(Vector2 dir)
{
	// collision acttion
	CollisionStart();
	moveDirection = dir;
	TakeDamage(2);
}