#pragma once
#include "../Friend_2D_EngineLib/Scene.h"
#include "../Friend_2D_EngineLib/GameObject.h"
#include "../Friend_2D_EngineLib/Transform.h"
#include "../Friend_2D_EngineLib/Camera.h"
#include "../Friend_2D_EngineLib/UI_Text.h"
#include "../Friend_2D_EngineLib/RectTransform.h"
#include "../Friend_2D_EngineLib/ScreenTextRenderer.h"
#include "../Friend_2D_EngineLib/Input.h"
#include "../Friend_2D_EngineLib/Time.h"
#include <vector>

class EndScene : public Scene
{
private:
	// ī�޶�
	GameObject* cam = nullptr;

	// ũ���� �ؽ�Ʈ���� ������ ����
	std::vector<UI_Text*> credits;

	// ��ũ�� ���� ����
	float scrollY = 0.0f;
	float scrollSpeed = 100.0f;  // �⺻ ��ũ�� �ӵ�

	float endTimer = 0.0f;  // ũ������ �������� Ȯ���ϱ� ���� Ÿ�̸�
	bool isEnded = false;  // ũ������ �������� ����

public:
	// Scene �����ֱ� �Լ���
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void Exit() override;
};