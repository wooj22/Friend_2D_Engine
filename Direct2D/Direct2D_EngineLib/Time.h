#pragma once
#include <windows.h>

class Time
{
private:
    static LARGE_INTEGER frequency;
    static LARGE_INTEGER initCounter;
    static LARGE_INTEGER prevCounter;
    static LARGE_INTEGER currentCounter;
    static float deltaTime;
    static float fixedDeltaTime;

public:
    static void Init();
    static void Update();

    static float GetDeltaTime();        // 이번 프레임 경과 시간
    static float GetFixedDeltaTime();
    static float GetTotalTime();        // 전체 경과 시간
};