#pragma once
#include <wrl/client.h> 
#include <d2d1_1.h>
#include "IRenderer.h"
#include "Transform.h"
#include "D2DRenderManager.h"

class BitmapRenderer : public IRenderer
{
public:
	BitmapRenderer() {};
	~BitmapRenderer() {}

	Transform transform;
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> bitmapImage;

	void Init();
	void Render() override;
	void UnInit();
};

