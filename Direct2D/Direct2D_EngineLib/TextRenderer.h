#pragma once
#include <wrl/client.h> 
#include <d2d1_1.h>
#include <string>
#include "RenderSystem.h"
#include "IRenderer.h"

/* [Text Renderer Conponent]
* <World>의 Text 출력을 담당하는 Component로
* 컴포넌트 생성시 RenderSystem에 등록되어 text를 계속 render한다.
* 게임 콘텐츠에서 text, font, size, color, layout을 지정할 수 있다. (dirty 패턴 활용)
* render시 필요한 transform은 이 컴포넌트가 등록된 오브젝트의 transform을 포인터에 담아 활용한다
*/

class Transform;
class TextRenderer : public IRenderer
{
private:
	D2D1_POINT_2F centerPoint;
	Transform* transform;

	// text
	std::wstring text = L"";
	float fontSize = 32.0f;
	std::wstring fontName = L"맑은 고딕";
	D2D1_COLOR_F textColor = D2D1::ColorF(D2D1::ColorF::White);
	int width = 100;
	int height = 100;

	// d2d
	ComPtr<ID2D1SolidColorBrush> brush;
	ComPtr<IDWriteTextFormat> textFormat;
	ComPtr<IDWriteTextLayout> textLayout;

	bool isTextDirty;

public:
	// component cycle
	TextRenderer() { RenderSystem::Get().Regist(this); };
	~TextRenderer() override { RenderSystem::Get().Unregist(this); }

	void OnEnable() override;
	void Update() override;
	void Render() override;
	void OnDestroy() override;

	// set
	void SetText(const std::wstring& newText);
	void SetFontSize(float newSize);
	void SetFontName(const std::wstring& newName);
	void SetColor(const D2D1_COLOR_F& newColor);
	void SetLayout(int width, int height);
};

