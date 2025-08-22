#pragma once
#include "../Direct2D_EngineLib/Script.h"


class PlayerFSM; 

// �÷��̾��� ���� �浹 ���� ��Ʈ�ѷ�
class PlayerAreaController : public Script
{
	PlayerFSM* playerFSM = nullptr; // �÷��̾� FSM

public:
	// script component cycle
	void Awake() override;
	void Start() override;
	void Update() override;
	void OnDestroy() override;

	// trigger event
	void OnTriggerEnter(ICollider* other, const ContactInfo& contact) override;
	void OnTriggerStay(ICollider* other, const ContactInfo& contact) override;
};