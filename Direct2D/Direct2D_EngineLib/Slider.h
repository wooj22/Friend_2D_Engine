#pragma once
#include "I_UI.h"
#include "MultiDelegate.h"
#include "UISystem.h"

/* [Slider Conponent]
* ���� ������Ʈ�� Gauge�� Handle�� �����Ͽ� �����̴� value�� ����ϰ�
* onValueChanged�̺�Ʈ�� �߻������ִ� ������Ʈ�̴�.
* 
* handle�� rect�� slideArea�� �ڽ���
* slideArea���� handle �巡��(x)�� �����Ͽ� handle�� ��ġ�� �ű�� -> handlePos.x/slideAreaSize.x = value
* value�� ���� gauge.fillAmount = value
* value�� �ٲ���� �����Ͽ� onValueChangedListeners�̺�Ʈ �߻�
*/

class RectTransform;
class ImageRenderer;
class Slider : public I_UI
{
private:
    float value = 0.5f;         // slider fill amount
    bool isDragging = false;

public:
    // Slider GameObject Reacttransfom (Area)
    RectTransform* slideArea = nullptr;
    
    // child component
    RectTransform* handle = nullptr;
    ImageRenderer* gauge = nullptr;

    // component cycle
    Slider() = default;
    ~Slider() override = default;

    void OnEnable_Inner() override final;
    void OnDisable_Inner() override final;
    void Update();
    void OnDestroy_Inner() override final;

public:
    // funcs
    float GetValue() { return value; }
    void SetValue(float v);
public:
    /* Event */
    MultiDelegate<> onValueChangedListeners;       // On Value Changed
    void OnValueChanged();
};

