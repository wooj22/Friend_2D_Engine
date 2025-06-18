#include "SpriteRenderer.h"

// Ãà º¸Á¤ data
//void BitmapRenderer::AxisCoreection() {
//	if (!image) return;
//
//	D2D1_SIZE_F size = image->GetSize();
//	destRect = {
//		-size.width / 2.0f,  // left
//		-size.height / 2.0f, // up
//		size.width / 2.0f,   // right
//		size.height / 2.0f   // down
//	};
//}

// render
void SpriteRenderer::Render() 
{
	if (!sprite) return;

	// center
	D2D1_SIZE_F size = sprite->GetSize();
	destRect = {
		-size.width / 2.0f,  // left
		-size.height / 2.0f, // up
		size.width / 2.0f,   // right
		size.height / 2.0f   // down
	};

	// render
	RenderSystem::Get().renderTarget->SetTransform(transform.GetScreenMatrix());
	RenderSystem::Get().renderTarget->DrawBitmap(sprite.Get(), destRect);
}

// uninit
void SpriteRenderer::UnInit()
{
	sprite = nullptr;
}