#include "Slider.h"
#include "RectTransform.h"
#include "ImageRenderer.h"
#include "GameObject.h"
#include "Input.h"
#include "ICollider.h"
#include <iostream>
#include <string>
#include <algorithm>

void Slider::OnEnable_Inner()
{
    UISystem::Get().Regist(this);
}

void Slider::OnDisable_Inner()
{
    UISystem::Get().Unregist(this);
}

void Slider::OnDestroy_Inner()
{
    UISystem::Get().Unregist(this);
}

void Slider::Update()
{
    if (!slideArea || !handle || !gauge)
        return;

    // mouse position
    Vector2 mousePos = Input::GetMouseScreenPosition();

    // slideArea
    Vector2 slideAreaWorldPos = slideArea->GetWorldPosition();
    Vector2 slideAreaSize = { slideArea->GetSize().width, slideArea->GetSize().height };
    Vector2 slideAreaMin = slideAreaWorldPos - slideAreaSize * 0.5f;
    Vector2 slideAreaMax = slideAreaWorldPos + slideAreaSize * 0.5f;

    // mouse Inside
    bool mouseInside =
        (mousePos.x >= slideAreaMin.x && mousePos.x <= slideAreaMax.x &&
            mousePos.y >= slideAreaMin.y && mousePos.y <= slideAreaMax.y);

    // drag
    if (Input::GetMouseButtonDown(0) && mouseInside) isDragging = true;
    if (Input::GetMouseButtonUp(0))isDragging = false;

    // slide
    if (isDragging)
    {
        // handle ���� ��ġ ���
        float localX = mousePos.x - slideAreaMin.x;
        float clampedX = clamp(localX, 0.0f, slideAreaSize.x);

        // handle
        Vector2 handlePos = handle->GetPosition();
        handlePos.x = clampedX-slideArea->GetSize().width / 2;          // �ϴ� �ϵ��ڵ�
        handle->SetPosition(handlePos);

        // value
        float newValue = clampedX / slideAreaSize.x;

        if (abs(newValue - value) > 0.0001f)
        {
            value = newValue;
            gauge->fillAmount = value;      // guage
            OnValueChanged();               // event
        }
    }
}

void Slider::SetValue(float v)
{
    value = clamp(v, 0.0f, 1.0f); // 0~1 ���� ����

    // handle
    if (slideArea && handle)
    {
        Vector2 slideAreaSize = { slideArea->GetSize().width, slideArea->GetSize().height };
        float clampedX = value * slideAreaSize.x;
        Vector2 handlePos = handle->GetPosition();
        handlePos.x = clampedX - slideAreaSize.x / 2.0f;
        handle->SetPosition(handlePos);
    }

    // gauge
    if (gauge)
        gauge->fillAmount = value;

    // event
    OnValueChanged();
}


// Event
void Slider::OnValueChanged()
{
    OutputDebugStringA("[Woo Engine] Slider Event! OnValueChanged()\n");
    // float value ����� ���
    char buffer[128];
    sprintf_s(buffer, "[Woo Engine] Slider value: %.3f\n", value);
    OutputDebugStringA(buffer);

    onValueChangedListeners.Invoke();
}