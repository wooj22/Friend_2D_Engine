#pragma once
#include "Component.h"

class ITransform : public Component
{
public:
	virtual ~ITransform() = default;
	virtual void Update() = 0;
};

// 현재 사용중인 클래스 목록
// Transform
// (RectTransform)