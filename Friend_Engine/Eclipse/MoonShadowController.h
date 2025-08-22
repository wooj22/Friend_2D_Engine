#pragma once
#include "../Friend_2D_EngineLib/Script.h"

// ���� �׸��� controller script

class Transform;
class MoonShadowController : public Script
{
private:
	Transform* tr;
	Transform* moonTr;
	float speed = 3.5f;
	bool isWaving = false;
	bool isBossWave = false;
	bool isStop = false;
	bool isAfterMoving = false;
	bool isDirecting = false;

public:
	void Awake() override;
	void Update() override;

	// ���� ����
	void DirectingBossWave();

	// ���� ���� ���� �ٽ� �̵�
	void AfterMovingStart();

	// ���� ���� ������ �÷���
	bool IsEclipseDirecting() { return isDirecting; }

	// ���� ���� restart
	void ReStart();
};

