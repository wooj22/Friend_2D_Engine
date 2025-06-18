#pragma once
#include <wrl/client.h> 
#include <d2d1_1.h>
#include "IRenderer.h"
#include "Transform.h"
#include "RenderSystem.h"

/* Sprite Render Conponent */
class SpriteRenderer : public IRenderer
{
private:
	D2D1_RECT_F destRect;

public:
	SpriteRenderer() { RenderSystem::Get().RenderListAdd(this); };
	~SpriteRenderer() {}

	Transform transform;
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> sprite;

	//void AxisCoreection();
	void Render() override;
	void UnInit() override;
};

