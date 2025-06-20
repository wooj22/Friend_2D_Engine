#pragma once
#include "GameObject.h"
#include "Transform.h"

class Camera : public GameObject
{
public:
	float width, height;
	Transform* transform;

	Camera() { }
	Camera(int w, int h) : width(w), height(h) {};
	~Camera() { }
	void SetSize(int w, int h) { width = w;	height = h; }

	// 사용 안함 (GameObject의 Component templete을 사용하기 위한 구조)
	// 게임 콘텐츠의 다른 스크립트에서 componenet만 get해서 제어 코드 작성
	void Start() override {}
	void Update() override {}
	void Destroy() override {}
};

