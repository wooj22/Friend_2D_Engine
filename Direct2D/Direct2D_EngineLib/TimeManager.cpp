#include "TimeManager.h"

void TimeManager::Init()
{
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&initCounter);
    prevCounter = initCounter;
}

void TimeManager::Update()
{
    QueryPerformanceCounter(&currentCounter);
    deltaTime = static_cast<float>(currentCounter.QuadPart - prevCounter.QuadPart) / frequency.QuadPart;
    prevCounter = currentCounter;
}

float TimeManager::GetDeltaTime()
{
    return deltaTime;
}

float TimeManager::GetTotalTime()
{
    float totalTime = static_cast<float>(currentCounter.QuadPart - initCounter.QuadPart) / frequency.QuadPart;
    return totalTime;
}