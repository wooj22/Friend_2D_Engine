#pragma once
#include "GameObject.h"
#include "RectTransform.h"
#include "ImageRenderer.h"
#include "Button.h"

/* [Button GameObject]
* Button에 필요한 멤버를 추가해둔 기본 Button GameObject
*/

class UI_Button : public GameObject
{
public:
	RectTransform* rectTransform;
	ImageRenderer* imageRenderer;
	// UI용 TextRenerer 만들면 추가하기
	Button* button;

	UI_Button() {}
	~UI_Button() override {}

	void Awake() override;
	void Start() override {}
	void Update() override {}
	void Destroy() override {}
};

