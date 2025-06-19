#include "TextRenderer.h"
#include "Transform.h"
#include "GameObject.h"

void TextRenderer::OnEnable() 
{
	transform = this->owner->GetComponent<Transform>();

	// 기본 브러시 및 텍스트 포맷
	RenderSystem::Get().renderTarget->CreateSolidColorBrush(textColor, brush.GetAddressOf());
	isTextDirty = true;
}

void TextRenderer::Update() 
{
	if (isTextDirty) {
		// 텍스트 포맷 재생성
		RenderSystem::Get().dWriteFactory->CreateTextFormat(
			fontName.c_str(),
			nullptr,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			fontSize,
			L"",  // locale
			textFormat.GetAddressOf()
		);
		textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

		// 텍스트 레이아웃 재생성
		RenderSystem::Get().dWriteFactory->CreateTextLayout(
			text.c_str(),
			static_cast<UINT32>(text.length()),
			textFormat.Get(),
			width, height,
			textLayout.GetAddressOf()
		);

		// center
		centerPoint = { -width / 2.0f,-height / 2.0f };

		isTextDirty = false;
	}
}

void TextRenderer::Render() 
{
	if (!transform || !textLayout) return;
	
	// render
	RenderSystem::Get().renderTarget->SetTransform(transform->GetScreenMatrix());
	RenderSystem::Get().renderTarget->DrawTextLayout(
		centerPoint,
		textLayout.Get(),
		brush.Get()
	);
}

void TextRenderer::OnDestroy() 
{
	brush = nullptr;
	textFormat = nullptr;
	textLayout = nullptr;
}

void TextRenderer::SetText(const std::wstring& newText)
{
	text = newText;
	isTextDirty = true;
}

void TextRenderer::SetFontSize(float newSize)
{
	fontSize = newSize;
	isTextDirty = true;
}

void TextRenderer::SetFontName(const std::wstring& newName)
{
	fontName = newName;
	isTextDirty = true;
}

void TextRenderer::SetColor(const D2D1_COLOR_F& newColor)
{
	textColor = newColor;
	if (brush) {
		brush->SetColor(textColor);
	}
	else {
		RenderSystem::Get().renderTarget->CreateSolidColorBrush(textColor, brush.GetAddressOf());
	}
}

void TextRenderer::SetLayout(int width, int height) 
{
	this->width = width; this->height = height;
	isTextDirty = true;
}