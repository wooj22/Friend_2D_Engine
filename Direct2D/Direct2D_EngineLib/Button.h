#pragma once
#include "Component.h"
#include "RectTransform.h"
#include "MultiDelegate.h"
#include "ButtonSystem.h"

class Button : public Component
{
private:
    RectTransform* rectTransform;       // Button ¿µ¿ª get¿ë

public:
    // event
    MultiDelegate<> onClickListeners;

public:
    // component cycle
    Button() { ButtonSystem::Get().Regist(this); }
    ~Button() override { ButtonSystem::Get().Unregist(this); }

    void OnEnable() override;
    void Update();
    void OnDestroy() override;

private:
    void OnClick();
};

