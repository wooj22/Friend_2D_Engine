#pragma once
#include <wrl/client.h> 
#include <d2d1_1.h>
#include "IRenderer.h"
#include "Transform.h"
#include "D2DRenderManager.h"

/* Bitmap Render Conponent */
// Render, UnInit은 Manager에서 호출하며 Manager와의 결합도를 낮추기 위해 인터페이스를 활용한다.
class BitmapRenderer : public IRenderer
{
private:
	D2D1_RECT_F destRect;

public:
	BitmapRenderer() { D2DRenderManager::Get().RenderListAdd(this); };
	~BitmapRenderer() {}

	Transform transform;
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> image;

	void AxisCoreection();
	void Render() override;
	void UnInit() override;
};

