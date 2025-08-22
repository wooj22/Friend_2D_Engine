#pragma once
#include "GameObject.h"
#include "RectTransform.h"
#include "ScreenTextRenderer.h"

/* [UI_Text GameObject]
* ���� ScreenText�� �ʿ��� ����� �߰��ص� �⺻ UI_Text GameObject
*/

class UI_Text : public GameObject
{
public:
	RectTransform* rectTransform;
	ScreenTextRenderer* screenTextRenderer;

	UI_Text() 
	{ 
		rectTransform = AddComponent<RectTransform>();
		screenTextRenderer = AddComponent <ScreenTextRenderer>();
	}
	~UI_Text() override { }
};
