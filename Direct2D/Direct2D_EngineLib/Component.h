#pragma once
#include <Windows.h>

class GameObject;
class Component
{
public:
    GameObject* owner = nullptr;

public:
    virtual ~Component() = default;
    
    virtual void OnEnable() = 0;
    virtual void OnDestroy() = 0;
};

