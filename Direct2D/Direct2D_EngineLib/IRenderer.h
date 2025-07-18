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
	// layer
	RenderType rendertype = RenderType::GameObject;
	int layer = 0;

	// culling

	// component cycle
	virtual ~IRenderer() = default;
	virtual void Update() = 0;
	virtual void Render() = 0;
};