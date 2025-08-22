#include "WorldTextRenderer.h"
#include "Transform.h"
#include "GameObject.h"

void WorldTextRenderer::OnEnable_Inner()
{
	RenderSystem::Get().Regist(this);
	transform = this->gameObject->GetComponent<Transform>();

	// brush ����
	RenderSystem::Get().renderTarget->CreateSolidColorBrush(textColor, brush.GetAddressOf());
	isTextDirty = true;
}

void WorldTextRenderer::OnDisable_Inner()
{
	RenderSystem::Get().Unregist(this);
	transform = nullptr;
}

void WorldTextRenderer::OnDestroy_Inner()
{
	RenderSystem::Get().Unregist(this);
	brush = nullptr;
	textFormat = nullptr;
	textLayout = nullptr;
}

void WorldTextRenderer::Update() 
{
	// bound update
	if (transform) 
	{
		Vector2 boundPos = transform->GetWorldPosition();
		Vector2 boundSize = Vector2(width, height);
	}

	// text update
	if (isTextDirty) {
		// �ؽ�Ʈ ���� �����
		RenderSystem::Get().dWriteFactory->CreateTextFormat(
			fontName.c_str(),              // ��Ʈ
			nullptr,                       // Ŀ���� ��Ʈ �÷��� (null�̸� �ý��� �⺻)
			DWRITE_FONT_WEIGHT_NORMAL,     // ����
			DWRITE_FONT_STYLE_NORMAL,      // ��Ÿ��(����� ����)
			DWRITE_FONT_STRETCH_NORMAL,    // ��Ʈ��Ī
			fontSize,                      // ũ��
			L"",                           // ������ (""�̸� �ý��� �⺻ ���)
			textFormat.GetAddressOf()
		);
		
		// ����
		textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

		// �ؽ�Ʈ ���̾ƿ� �����
		RenderSystem::Get().dWriteFactory->CreateTextLayout(
			text.c_str(),                       // ����� ���ڿ�
			static_cast<UINT32>(text.length()), // ���ڿ� ����
			textFormat.Get(),                   
			width, height,                      // ���̾ƿ� ũ��
			textLayout.GetAddressOf()
		);

		// center
		centerPoint = { -width / 2.0f,-height / 2.0f };

		isTextDirty = false;
	}
}

void WorldTextRenderer::Render() 
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

void WorldTextRenderer::SetText(const std::wstring& newText)
{
	text = newText;
	isTextDirty = true;
}

void WorldTextRenderer::SetFontSize(float newSize)
{
	fontSize = newSize;
	isTextDirty = true;
}

void WorldTextRenderer::SetFontName(const std::wstring& newName)
{
	fontName = newName;
	isTextDirty = true;
}

void WorldTextRenderer::SetColor(const D2D1_COLOR_F& newColor)
{
	textColor = newColor;
	if (brush) {
		brush->SetColor(textColor);
	}
	else {
		RenderSystem::Get().renderTarget->CreateSolidColorBrush(textColor, brush.GetAddressOf());
	}
}

void WorldTextRenderer::SetAlpha(float a)
{
	alpha = a;
	if (brush) brush->SetOpacity(alpha);
}

void WorldTextRenderer::SetLayout(int width, int height) 
{
	this->width = width; this->height = height;
	isTextDirty = true;
}


void WorldTextRenderer::SetHorizontalAlign(TextHorizontalAlign align)
{
	horizontalAlign = align;
	isTextDirty = true;
}

void WorldTextRenderer::SetVerticalAlign(TextVerticalAlign align)
{
	verticalAlign = align;
	isTextDirty = true;
}

inline DWRITE_TEXT_ALIGNMENT WorldTextRenderer::ToDWriteTextAlignment(TextHorizontalAlign align)
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

inline DWRITE_PARAGRAPH_ALIGNMENT WorldTextRenderer::ToDWriteParagraphAlignment(TextVerticalAlign align)
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