#include "ImageRenderer.h"
#include "RectTransform.h"
#include "GameObject.h"

void ImageRenderer::OnEnable()
{
	rectTransform = this->owner->GetComponent<RectTransform>();

	// brush »ý¼º
	RenderSystem::Get().renderTarget->CreateSolidColorBrush(textColor, brush.GetAddressOf());
}

void ImageRenderer::Update()
{

}

void ImageRenderer::Render()
{
    if (!rectTransform) return;

    // tansform
    RenderSystem::Get().renderTarget->SetTransform(rectTransform->GetScreenMatrix());

    // rect
    auto size = rectTransform->GetSize();
    destRect = { 0.0f, 0.0f, size.width, size.height };

    // render
    if (sprite)
        RenderSystem::Get().renderTarget->DrawBitmap(sprite->texture->texture2D.Get(), destRect);
    else
        RenderSystem::Get().renderTarget->FillRectangle(destRect, brush.Get());
}

void ImageRenderer::OnDestroy() 
{
	sprite = nullptr;
}