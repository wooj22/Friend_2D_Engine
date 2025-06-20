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

