#pragma once
#include "GameObject.h"
#include "RectTransform.h"
#include "ImageRenderer.h"
#include "Button.h"

/* [Button GameObject]
* Button에 필요한 멤버를 추가해둔 기본 Button GameObject
* 게임 콘텐츠에서 Button은 이 클래스를 상속받아 override하면 된다.
* 코드 구현이 아예 없으므로 addComponent부터 해주어야한다.
*/

class UI_Button : public GameObject
{
protected:
	RectTransform* rectTransform;
	ImageRenderer* imageRenderer;
	// UI용 TextRenerer 만들면 추가하기
	Button* button;

public:
	UI_Button() {}
	~UI_Button() override {}

	void Awake() override {};
	void Start() override {};
	void Update() override {};
	void Destroy() override {};
};

