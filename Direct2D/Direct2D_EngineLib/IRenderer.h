#pragma once
#include "Component.h"

/* Renderer Componenets Interface */

enum class RenderType
{
	UI, GameObject
};

enum class TextHorizontalAlign {
	Left,
	Center,
	Right
};

enum class TextVerticalAlign {
	Top,
	Center,
	Bottom
};

class IRenderer : public Component
{
public : 
	virtual ~IRenderer() = default;

	virtual void Update() = 0;
	virtual void Render() = 0;

	// gameobject 위에 ui 그리기 (일단 이렇게 함)
	RenderType rendertype = RenderType::GameObject;
};