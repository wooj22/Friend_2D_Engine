#pragma once
#include <functional>
#include <vector>
#include "Time.h"

struct InvokeTask
{
    float timeRemaining;
    std::function<void()> func;
};

// �Լ� ���� ó��
class InvokeSystem
{
private:
    static std::vector<InvokeTask> tasks;

public:
    static void Invoke(float delay, std::function<void()> func);

    template<typename T>
    static void Invoke(float delay, T* instance, void (T::* method)());

    static void Update();
};
