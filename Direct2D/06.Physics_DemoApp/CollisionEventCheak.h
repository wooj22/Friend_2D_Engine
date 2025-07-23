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
	void OnCollisionEnter(ICollider* other, const ContactInfo& contact)  override
	{
		// contact info 에 대한 내용으로 text set
		wchar_t buffer[256];
		swprintf_s(buffer, 256, L"Enter\nNormal: (%.3f, %.3f)\nDepth: %.3f",
			contact.normal.x, contact.normal.y, contact.depth);
		text->SetText(buffer);

		//text->SetText(L"OnCollisionEnter()");
	}

	// collision stay
	void OnCollisionStay(ICollider* other, const ContactInfo& contact) override
	{
		// contact info 에 대한 내용으로 text set
		wchar_t buffer[256];
		swprintf_s(buffer, 256, L"Stay\nNormal: (%.3f, %.3f)\nDepth: %.3f",
			contact.normal.x, contact.normal.y, contact.depth);
		text->SetText(buffer);

		//text->SetText(L"OnCollisionStay()");
	}

	// collision exit
	void OnCollisionExit(ICollider* other, const ContactInfo& contact)  override
	{
		// contact info 에 대한 내용으로 text set
		wchar_t buffer[256];
		swprintf_s(buffer, 256, L"Exit\nNormal: (%.3f, %.3f)\nDepth: %.3f",
			contact.normal.x, contact.normal.y, contact.depth);
		text->SetText(buffer);

		//text->SetText(L"OnCollisionExit()");
	}
};

