#pragma once
#include "../Friend_2D_EngineLib/GameObject.h"
#include "../Friend_2D_EngineLib/Transform.h"
#include "../Friend_2D_EngineLib/SpriteRenderer.h"
#include "../Friend_2D_EngineLib/Rigidbody.h"
#include "../Friend_2D_EngineLib/CircleCollider.h"
#include "../Friend_2D_EngineLib/Animator.h"
#include "../Friend_2D_EngineLib/AudioSource.h"
#include "../Friend_2D_EngineLib/AudioClip.h"
#include "../Friend_2D_EngineLib/ResourceManager.h"
#include "HonCAnimatorController.h"
#include "HonCController.h"

/* Darkness ����� ȥ */

class HonC : public GameObject
{
public:
	// components
	Transform* transform;
	SpriteRenderer* spriteRenderer;
	Rigidbody* rigidbody;
	CircleCollider* collider;
	Animator* animator;
	AudioSource* audioSource;
	HonCController* controller;

	// animator controller asset
	HonCAnimatorController* animatorController;

	HonC() : GameObject("HonC", "Hon")		// name, tag
	{
		transform = AddComponent<Transform>();
		spriteRenderer = AddComponent<SpriteRenderer>();
		rigidbody = AddComponent<Rigidbody>();
		collider = AddComponent<CircleCollider>();
		animator = AddComponent<Animator>();
		audioSource = AddComponent<AudioSource>();
		controller = AddComponent<HonCController>();

		// animator
		animatorController = new HonCAnimatorController();
		animator->SetController(animatorController);

		// renderer set
		spriteRenderer->renderMode = RenderMode::Lit_Glow;
		spriteRenderer->layer = 11;

		// physics set
		rigidbody->useGravity = false;
		rigidbody->isKinematic = true;
		collider->isTrigger = true;
		collider->offset = { 0, -15 };
		collider->radius = 40;

		// audio chnnel set
		audioSource->SetChannelGroup(AudioSystem::Get().GetSFXGroup());
		audioSource->SetLoop(false);
	}

	~HonC()
	{
		delete animatorController;
	}
};

