#pragma once
#include "../Direct2D_EngineLib/Script.h"
#include "../Direct2D_EngineLib/Input.h"
#include "../Direct2D_EngineLib/Rigidbody.h"

class PlayerMove : public Script
{
private:
	float inputX, inputY, speed = 500.0f;
	Transform* transform;
	Rigidbody* rigid;
	bool isWave = false;

public: 
	void OnEnable() override;				// ������Ʈ Ȱ��ȭ ����)
	void Update() override;					// �� ������ �ݺ� ȣ��
	void OnTriggerStay(ICollider* other, const ContactInfo& contact) override;
};

