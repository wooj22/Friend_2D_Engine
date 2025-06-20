#include "Time.h"

LARGE_INTEGER Time::frequency = {};
LARGE_INTEGER Time::initCounter = {};
LARGE_INTEGER Time::prevCounter = {};
LARGE_INTEGER Time::currentCounter = {};
float Time::deltaTime = 0.0f;

void Time::Init()
{
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&initCounter);
    prevCounter = initCounter;
}

void Time::Update()
{
    QueryPerformanceCounter(&currentCounter);
    deltaTime = static_cast<float>(currentCounter.QuadPart - prevCounter.QuadPart) / frequency.QuadPart;
    prevCounter = currentCounter;
}

float Time::GetDeltaTime()
{
    return deltaTime;
}

float Time::GetTotalTime()
{
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    return static_cast<float>(now.QuadPart - initCounter.QuadPart) / frequency.QuadPart;
}
