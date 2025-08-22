#pragma once
#include "GameObject.h"
#include "RectTransform.h"
#include "ImageRenderer.h"

/* [UI_Image GameObject]
* ���� Image�� �ʿ��� ����� �߰��ص� �⺻ UI_Image GameObject
*/

class UI_Image : public GameObject
{
public:
	RectTransform* rectTransform;
	ImageRenderer* imageRenderer;

	UI_Image() 
	{ 
		rectTransform = AddComponent<RectTransform>();
		imageRenderer = AddComponent <ImageRenderer>(); 
	}
	~UI_Image() override {  }
};

