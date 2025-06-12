#pragma once
#include <windows.h>
#include "Singleton.h"

class TimeManager : public Singleton<TimeManager>
{
private:
	LARGE_INTEGER frequency;
	LARGE_INTEGER prevCounter;
	LARGE_INTEGER currentCounter;
	LARGE_INTEGER initCounter;
	float deltaTime;

public:
	TimeManager() = default;
	~TimeManager() override = default;

	void Init();
	void Update();
	void Release() {};

	float GetDeltaTime();
	float GetTotalTime();
};