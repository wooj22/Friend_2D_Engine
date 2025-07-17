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

	// gameobject À§¿¡ ui ±×¸®±â
	RenderType rendertype = RenderType::GameObject;

	// layer: ³·À»¼ö·Ï ¸ÕÀú ·»´õµÊ
	int layer = 0;
};