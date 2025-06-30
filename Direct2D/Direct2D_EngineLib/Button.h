#pragma once
#include "Component.h"
#include "MultiDelegate.h"
#include "ButtonSystem.h"

/* [Button Conponent]
* <UI>의 일정 영역의 onClick() 이벤트를 감시하고 발생하는 컴포넌트
* RectTransform을 포함한 GameObject에 등록되어야 정상적인 Button의 기능을 활용할 수 있다.
*/

class RectTransform;
class Button : public Component
{
private:
    RectTransform* rectTransform;     // button 영역 get

public:
    MultiDelegate<> onClickListeners; // callback functions

public:
    // component cycle
    Button() 
    { 
        ButtonSystem::Get().Regist(this); 
        OutputDebugStringA("Button()\n");
    }
    ~Button() override
    {
        ButtonSystem::Get().Unregist(this); 
        OutputDebugStringA("~Button()\n");
    }

    void OnEnable() override;
    void Update();
    void OnDestroy() override;

private:
    void OnClick(); // event
};

