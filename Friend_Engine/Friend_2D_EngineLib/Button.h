#pragma once
#include "I_UI.h"
#include "MultiDelegate.h"
#include "UISystem.h"

/* [Button Conponent]
* <UI>�� ���� ������ OnClick() �̺�Ʈ�� �����ϰ� �߻���Ű�ϴ� ������Ʈ
* �̺�Ʈ �߻��� onClickListeners�� ��ϵ� �ݹ� �Լ��� ��� ȣ���Ų��.
* RectTransform�� ������ GameObject�� ��ϵǾ�� �������� Button�� ����� Ȱ���� �� �ִ�.
*/

class RectTransform;
class Button : public I_UI
{
private:
    RectTransform* rectTransform; 

public:
    // component cycle
    Button() = default;
    ~Button() override = default;

    void OnEnable_Inner() override final;
	void OnDisable_Inner() override final;
    void Update();
    void OnDestroy_Inner() override final;

private:
    bool isMouseInside = false;

public:
    /* Event */
    MultiDelegate<> onClickListeners;       // On Click
    MultiDelegate<> onPointEnterListeners;  // On Point Enter
    MultiDelegate<> onPointExitListeners;   // On Point Exit

private:
    void OnClick();
    void OnPointEnter();
    void OnPointExit();
};

