#include "ScreenTextRenderer.h"
#include "RectTransform.h"
#include "GameObject.h"
#include "RenderSystem.h"

void ScreenTextRenderer::OnEnable_Inner()
{
	RenderSystem::Get().Regist(this);
	rectTransform = this->gameObject->rectTransform;

	// brush ����
	RenderSystem::Get().renderTarget->CreateSolidColorBrush(textColor, brush.GetAddressOf());
	isTextDirty = true;
}

void ScreenTextRenderer::OnDisable_Inner()
{
	RenderSystem::Get().Unregist(this);
	rectTransform = nullptr;
}

void ScreenTextRenderer::OnDestroy_Inner()
{
	RenderSystem::Get().Unregist(this);
	brush = nullptr;
	textFormat = nullptr;
	textLayout = nullptr;
}

void ScreenTextRenderer::Update()
{
	if (isTextDirty) {
		// �ؽ�Ʈ ���� �����
		RenderSystem::Get().dWriteFactory->CreateTextFormat(
			fontName.c_str(),              // ��Ʈ
			nullptr,				       // Ŀ���� ��Ʈ �÷��� (null�̸� �ý��� �⺻)
			DWRITE_FONT_WEIGHT_NORMAL,     // ����
			DWRITE_FONT_STYLE_NORMAL,      // ��Ÿ��(����� ����)
			DWRITE_FONT_STRETCH_NORMAL,    // ��Ʈ��Ī
			fontSize,                      // ũ��
			L"",                           // ������ (""�̸� �ý��� �⺻ ���)
			textFormat.GetAddressOf()
		);

		// ����
		textFormat->SetTextAlignment(ToDWriteTextAlignment(horizontalAlign));
		textFormat->SetParagraphAlignment(ToDWriteParagraphAlignment(verticalAlign));

		// �ؽ�Ʈ ���̾ƿ� �����
		RenderSystem::Get().dWriteFactory->CreateTextLayout(
			text.c_str(),
			static_cast<UINT32>(text.length()),
			textFormat.Get(),
			rectTransform->GetSize().width, rectTransform->GetSize().height,
			textLayout.GetAddressOf()
		);

		// center  (���� �ʿ�. rectTransform�� pivot�� ������)
		//centerPoint = { -rectTransform->GetSize().width / 2.0f,-rectTransform->GetSize().height / 2.0f };

		isTextDirty = false;
	}
}

void ScreenTextRenderer::Render()
{
	if (!rectTransform || !textLayout) return;

	// render
	RenderSystem::Get().renderTarget->SetTransform(rectTransform->GetScreenMatrix());
	RenderSystem::Get().renderTarget->DrawTextLayout(
		{0,0}, textLayout.Get(), brush.Get());
}

void ScreenTextRenderer::SetText(const std::wstring& newText)
{
	text = newText;
	isTextDirty = true;
}

void ScreenTextRenderer::SetFontSize(float newSize)
{
	fontSize = newSize;
	isTextDirty = true;
}

void ScreenTextRenderer::SetFontName(const std::wstring& newName)
{
	fontName = newName;
	isTextDirty = true;
}

void ScreenTextRenderer::SetColor(const D2D1_COLOR_F& newColor)
{
	textColor = newColor;
	if (brush) {
		brush->SetColor(textColor);
	}
	else {
		RenderSystem::Get().renderTarget->CreateSolidColorBrush(textColor, brush.GetAddressOf());
	}
}

void ScreenTextRenderer::SetAlpha(float a)
{
	alpha = a;
	if (brush) brush->SetOpacity(alpha);
}

void ScreenTextRenderer::SetHorizontalAlign(TextHorizontalAlign align)
{
	horizontalAlign = align;
	isTextDirty = true;
}

void ScreenTextRenderer::SetVerticalAlign(TextVerticalAlign align)
{
	verticalAlign = align;
	isTextDirty = true;
}

inline DWRITE_TEXT_ALIGNMENT ScreenTextRenderer::ToDWriteTextAlignment(TextHorizontalAlign align)
{
	switch (align)
	{
	case TextHorizontalAlign::Left:
		return DWRITE_TEXT_ALIGNMENT_LEADING;
	case TextHorizontalAlign::Center:
		return DWRITE_TEXT_ALIGNMENT_CENTER;
	case TextHorizontalAlign::Right:
		return DWRITE_TEXT_ALIGNMENT_TRAILING;
	default:
		return DWRITE_TEXT_ALIGNMENT_CENTER;
	}
}

inline DWRITE_PARAGRAPH_ALIGNMENT ScreenTextRenderer::ToDWriteParagraphAlignment(TextVerticalAlign align)
{
	switch (align)
	{
	case TextVerticalAlign::Top:
		return DWRITE_PARAGRAPH_ALIGNMENT_NEAR;
	case TextVerticalAlign::Center:
		return DWRITE_PARAGRAPH_ALIGNMENT_CENTER;
	case TextVerticalAlign::Bottom:
		return DWRITE_PARAGRAPH_ALIGNMENT_FAR;
	default:
		return DWRITE_PARAGRAPH_ALIGNMENT_CENTER;
	}
}