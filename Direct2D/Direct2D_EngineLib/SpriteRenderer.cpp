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

	// center 보정, 그릴 영역 지정
	D2D1_SIZE_F size = sprite->GetSize();
	centerRect = {
		-size.width / 2.0f,  // left
		-size.height / 2.0f, // up
		size.width / 2.0f,   // right
		size.height / 2.0f   // down
	};
	
	// render
	RenderSystem::Get().renderTarget->SetTransform(transform->GetScreenMatrix());
	RenderSystem::Get().renderTarget->DrawBitmap(sprite.Get(), centerRect);
}

void SpriteRenderer::OnDestroy()
{
	sprite = nullptr;
}

void SpriteRenderer::SetImage(const wchar_t* path) 
{
	RenderSystem::Get().CreateBitmapFromFile(path, this->sprite.GetAddressOf());
}