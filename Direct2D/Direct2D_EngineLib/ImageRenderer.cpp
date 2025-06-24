#include "ImageRenderer.h"
#include "RectTransform.h"
#include "GameObject.h"

void ImageRenderer::OnEnable()
{
	rectTransform = this->owner->GetComponent<RectTransform>();

	// brush 생성
	RenderSystem::Get().renderTarget->CreateSolidColorBrush(textColor, brush.GetAddressOf());
}

void ImageRenderer::Update()
{

}

void ImageRenderer::Render()
{
	if (!rectTransform) return;

    // pivot이 적용된 위치
	RenderSystem::Get().renderTarget->SetTransform(rectTransform->GetScreenMatrix());

    // pivot이 이미 적용되어 있으므로 그릴 영역만 지정
    auto size = rectTransform->GetSize();
    if (sprite)
    {
        D2D1_SIZE_F spriteSize = sprite->GetSize();
        rect = { 0.0f, 0.0f, size.width, size.height };
        RenderSystem::Get().renderTarget->DrawBitmap(sprite.Get(), rect);
    }
    else
    {
        // sprite가 없을 경우 white box 그리기
        rect = { 0.0f, 0.0f, size.width, size.height };
        RenderSystem::Get().renderTarget->FillRectangle(rect, brush.Get());
    }
}

void ImageRenderer::OnDestroy() 
{
	sprite = nullptr;
}

void ImageRenderer::SetImage(const wchar_t* path)
{
	RenderSystem::Get().CreateBitmapFromFile(path, this->sprite.GetAddressOf());
}