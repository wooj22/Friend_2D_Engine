#include "BitmapRenderer.h"

void BitmapRenderer::Render() 
{
	// device context draw bitmap
	D2DRenderManager::Get().renderTarget->DrawBitmap(image.Get());
}

void BitmapRenderer::UnInit()
{
	image = nullptr;
}