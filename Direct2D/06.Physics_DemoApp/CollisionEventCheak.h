#pragma once
#include "../Direct2D_EngineLib/Script.h"
#include "../Direct2D_EngineLib/WorldTextRenderer.h"

class CollisionEventCheak : public Script
{
public:
	WorldTextRenderer* text;	// ref

public:
	void OnEnable() override {}
	void Awake() override {}
	void Start() override {}
	void Update() override {}
	void FixedUpdate() override {}
	void OnDestroy() override {}
	
	// trigger enter
	void OnTriggerEnter(ICollider* other) override 
	{
		text->SetText(L"OnTriggerEnter()");
	}

	// trigger stay
	void OnTriggerStay(ICollider* other)  override 
	{ 
		text->SetText(L"OnTriggerStay()");
	}

	// trigger exit
	void OnTriggerExit(ICollider* other)  override 
	{
		text->SetText(L"OnTriggerExit()");
	}

	// collision enter
	void OnCollisionEnter(ICollider* other)  override
	{
		text->SetText(L"OnCollisionEnter()");
	}

	// collision stay
	void OnCollisionStay(ICollider* other) override
	{
		text->SetText(L"OnCollisionStay()");
	}

	// collision exit
	void OnCollisionExit(ICollider* other)  override
	{
		text->SetText(L"OnCollisionExit()");
	}
};

