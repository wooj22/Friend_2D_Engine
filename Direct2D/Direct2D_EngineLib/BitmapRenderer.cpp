#include "BitmapRenderer.h"

void BitmapRenderer::Render() 
{
	D2DRenderManager::Get().renderTarget->SetTransform(transform.GetWorldMatrix());
	D2DRenderManager::Get().renderTarget->DrawBitmap(image.Get());
}

void BitmapRenderer::UnInit()
{
	image = nullptr;
}