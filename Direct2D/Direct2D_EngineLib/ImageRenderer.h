#pragma once
#include <wrl/client.h> 
#include <d2d1_1.h>
#include "IRenderer.h"
#include "RenderSystem.h"

#include "Texture2D.h"
#include "ResourceManager.h"
#include "iostream"

/* [Image Renderer Conponent]
* <UI>의 이미지 한 장(sprite)의 render를 담당하는 component로
* 컴포넌트 생성시 RenderSystem에 등록되어 sprite를 게속 render한다.
* sprite가 있다면 sprite 출력, 없다면 white box 칠하기
* render시 필요한 rectTransform은 이 컴포넌트가 등록된 오브젝트의 rectTransform을 포인터에 담아 활용한다
*/

class RectTransform;
class ImageRenderer : public IRenderer
{
private:
	RectTransform* rectTransform;
	D2D1_RECT_F rect;
	shared_ptr<Texture2D> sprite;	// 공유 자원  // TODO :: Sptie Class 만들기

	// sprite가 없을 경우 box draw
	ComPtr<ID2D1SolidColorBrush> brush;
	D2D1_COLOR_F textColor = D2D1::ColorF(D2D1::ColorF::White);

public:
	// component cycle
	ImageRenderer() { 
		RenderSystem::Get().Regist(this);
		OutputDebugStringA("ImageRenderer()\n");
	};
	~ImageRenderer() override 
	{
		RenderSystem::Get().Unregist(this); 
		OutputDebugStringA("~ImageRenderer()\n");
	}

	void OnEnable() override;
	void Update() override;
	void Render() override;
	void OnDestroy() override;

public:
	// function
	void CreateTexture2D(const std::string& path)
	{
		sprite = ResourceManager::Get().CreateTexture2D(path);
	}
};

