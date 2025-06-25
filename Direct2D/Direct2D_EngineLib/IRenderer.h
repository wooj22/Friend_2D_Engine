#pragma once
#include "Component.h"

/* Renderer Componenets Interface */

class IRenderer : public Component
{
public : 
	virtual ~IRenderer() = default;

	virtual void Update() = 0;
	virtual void Render() = 0;
};

// 현재 사용중인 클래스 목록
// SpriteRenderer
// TextRenderer
// RenderSystem
// ScreenTextRenderer