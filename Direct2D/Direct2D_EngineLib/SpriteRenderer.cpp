#include "SpriteRenderer.h"
#include "Transform.h"
#include "GameObject.h"

void SpriteRenderer::OnEnable() 
{
	transform = this->owner->GetComponent<Transform>();
}

void SpriteRenderer::Update() 
{

}

void SpriteRenderer::Render() 
{
	if (!transform || !sprite) return;

	// source rect, size
	D2D1_RECT_F srcRect = sprite->sourceRect;
	D2D1_SIZE_F spriteSize = sprite->size;

	// pivox
	float pivotX = sprite->pivot.x;
	float pivotY = 1.0f - sprite->pivot.y;

	// dest rect
	destRect = {
		-spriteSize.width * pivotX,
		-spriteSize.height * pivotY,
		spriteSize.width * (1.0f - pivotX),
		spriteSize.height * (1.0f - pivotY)
	};

	// filp
	float scaleX = flipX ? -1.0f : 1.0f;
	float scaleY = flipY ? -1.0f : 1.0f;
	D2D1::Matrix3x2F flipMat = D2D1::Matrix3x2F::Scale(scaleX, scaleY, { 0, 0 });
	auto finalMat = flipMat * transform->GetScreenMatrix();

	// transform
	RenderSystem::Get().renderTarget->SetTransform(finalMat);
	
	// render
	RenderSystem::Get().renderTarget->SetTransform(finalMat);
	RenderSystem::Get().renderTarget->DrawBitmap(
		sprite->texture->texture2D.Get(),
		destRect,           // 출력 위치 및 크기
		alpha,				// 불투명도
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		srcRect             // source rect
	);
}

void SpriteRenderer::OnDestroy()
{
	sprite = nullptr;
}