#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h"
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/Rigidbody.h"
#include "../Direct2D_EngineLib/CircleCollider.h"
#include "../Direct2D_EngineLib/Animator.h"
#include "../Direct2D_EngineLib/AudioSource.h"
#include "../Direct2D_EngineLib/AudioClip.h"
#include "../Direct2D_EngineLib/ResourceManager.h"
#include "HonAAnimatorController.h"
#include "HonAController.h"

/* Ignis ���� ȥ*/

class HonA : public GameObject
{
public:
	// components
	Transform* transform;
	SpriteRenderer* spriteRenderer;
	Rigidbody* rigidbody;
	CircleCollider* collider;
	Animator* animator;
	AudioSource* audioSource;
	HonAController* controller;

	// animator controller asset
	HonAAnimatorController* animatorController;

	HonA() : GameObject("HonA", "Hon")		// name, tag
	{
		transform = AddComponent<Transform>();
		spriteRenderer = AddComponent<SpriteRenderer>();
		rigidbody = AddComponent<Rigidbody>();
		collider = AddComponent<CircleCollider>();
		animator = AddComponent<Animator>();
		audioSource = AddComponent<AudioSource>();
		controller = AddComponent<HonAController>();

		// animator
		animatorController = new HonAAnimatorController();
		animator->SetController(animatorController);

		// renderer set
		spriteRenderer->renderMode = RenderMode::Lit_Glow;
		spriteRenderer->layer = 11;

		// physics set
		rigidbody->useGravity = false;
		rigidbody->isKinematic = true;
		collider->isTrigger = true;
		collider->offset = { 0, -5 };
		collider->radius = 40;

		// audio chnnel set
		audioSource->SetChannelGroup(AudioSystem::Get().GetSFXGroup());
		audioSource->SetLoop(false);
	}

	~HonA() 
	{
		delete animatorController;
	}
};

