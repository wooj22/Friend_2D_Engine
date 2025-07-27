#include "ImageRenderer.h"
#include "RectTransform.h"
#include "GameObject.h"

void ImageRenderer::OnEnable()
{
	rectTransform = this->gameObject->GetComponent<RectTransform>();

	// brush »ý¼º
	RenderSystem::Get().renderTarget->CreateSolidColorBrush(baseColor, brush.GetAddressOf());
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

void ImageRenderer::SetBaseColor(const D2D1_COLOR_F& newColor) 
{
    baseColor = newColor;
    if (brush) {
        brush->SetColor(baseColor);
    }
    else {
        RenderSystem::Get().renderTarget->CreateSolidColorBrush(baseColor, brush.GetAddressOf());
    }
}