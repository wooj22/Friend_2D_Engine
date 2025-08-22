#pragma once
#include "../Friend_2D_EngineLib/Script.h"
#include "../Friend_2D_EngineLib/Input.h"
#include "../Friend_2D_EngineLib/Rigidbody.h"

class NPCInteraction : public Script
{
private:
	GameObject* interactionImage;
public:
	NPCInteraction() : interactionImage(nullptr) {};
	~NPCInteraction() { interactionImage = nullptr; }

	void OnTriggerStay(ICollider* other, const ContactInfo& contact) override;
	void OnTriggerExit(ICollider* other, const ContactInfo& contact) override;
	void Update() override;
	void SetNPC(GameObject* setimage) { interactionImage = setimage; }
};

