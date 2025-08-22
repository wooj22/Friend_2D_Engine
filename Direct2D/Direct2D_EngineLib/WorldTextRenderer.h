#pragma once
#include <wrl/client.h> 
#include <d2d1_1.h>
#include <string>
#include "RenderSystem.h"
#include "IRenderer.h"

/* [World Text Renderer Conponent]
* <World>�� Text ����� ����ϴ� Component��
* ������Ʈ ������ RenderSystem�� ��ϵǾ� text�� ��� render�Ѵ�.
* ���� ���������� text, font, size, color, layout�� ������ �� �ִ�. (dirty ���� Ȱ��)
* UI�� �ƴ� World�� Text�� GameObject�� Transform(position)�� �����Ͽ� 
* ���θ��� size(width, height)�� ���� center�� �����Ͽ� �߾ӿ� ����Ѵ�
* render�� �ʿ��� transform�� �� ������Ʈ�� ��ϵ� ������Ʈ�� transform�� �����Ϳ� ��� Ȱ���Ѵ�
*/

class Transform;
class WorldTextRenderer : public IRenderer
{
private:
	D2D1_POINT_2F centerPoint;	// text�� �߽��� gameobect�� position���� �� �� �ְ� �ϴ� render point
	Transform* transform;

	// text
	std::wstring text = L"";
	float fontSize = 32.0f;
	std::wstring fontName = L"Noto Serif KR";
	D2D1_COLOR_F textColor = D2D1::ColorF(D2D1::ColorF::White);
	int width = 100;
	int height = 100;
	float alpha = 1.0f;

	// align
	TextHorizontalAlign horizontalAlign = TextHorizontalAlign::Center;
	TextVerticalAlign verticalAlign = TextVerticalAlign::Center;

	// d2d
	ComPtr<ID2D1SolidColorBrush> brush;
	ComPtr<IDWriteTextFormat> textFormat;
	ComPtr<IDWriteTextLayout> textLayout;

	bool isTextDirty;

public:
	// component cycle
	WorldTextRenderer() = default;
	~WorldTextRenderer() override = default;
	void OnEnable_Inner() override final;
	void OnDisable_Inner() override final;
	void Update() override final;
	void Render() override final;
	void OnDestroy_Inner() override final;

	// set
	void SetText(const std::wstring& newText);
	void SetFontSize(float newSize);
	void SetFontName(const std::wstring& newName);
	void SetColor(const D2D1_COLOR_F& newColor);
	void SetLayout(int width, int height);
	void SetAlpha(float a);

	// align
	void SetHorizontalAlign(TextHorizontalAlign align);
	void SetVerticalAlign(TextVerticalAlign align);

private:
	// align
	DWRITE_TEXT_ALIGNMENT ToDWriteTextAlignment(TextHorizontalAlign align);
	DWRITE_PARAGRAPH_ALIGNMENT ToDWriteParagraphAlignment(TextVerticalAlign align);
};