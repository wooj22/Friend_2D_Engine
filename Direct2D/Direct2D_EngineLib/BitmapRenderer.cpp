#include "BitmapRenderer.h"

// Ãà º¸Á¤ data
void BitmapRenderer::AxisCoreection() {
	if (!image) return;

	D2D1_SIZE_F size = image->GetSize();
	destRect = {
		-size.width / 2.0f,  // left
		-size.height / 2.0f, // up
		size.width / 2.0f,   // right
		size.height / 2.0f   // down
	};
}

// render
void BitmapRenderer::Render() 
{
	D2DRenderManager::Get().renderTarget->SetTransform(transform.GetScreenMatrix());
	D2DRenderManager::Get().renderTarget->DrawBitmap(image.Get(), destRect);
}

// uninit
void BitmapRenderer::UnInit()
{
	image = nullptr;
}