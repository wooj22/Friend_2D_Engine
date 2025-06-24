#include "Button.h"

void Button::OnEnable() 
{

}

void Button::Update() 
{
	OnClick();
}

void Button::OnDestroy() 
{

}

inline void Button::OnClick()
{
	// 만약 이 버튼이 클릭됐다면
	onClickListeners.Invoke();
}