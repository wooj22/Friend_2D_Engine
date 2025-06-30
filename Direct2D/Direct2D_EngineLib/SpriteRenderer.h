#pragma once
#include <wrl/client.h> 
#include <d2d1_1.h>
#include "IRenderer.h"
#include "RenderSystem.h"

/* [Sprite Renderer Conponent]
* <World>의 이미지 한 장(sprite)의 render를 담당하는 component로
* 컴포넌트 생성시 RenderSystem에 등록되어 sprite를 게속 render한다.
* render시 필요한 transform은 이 컴포넌트가 등록된 오브젝트의 transform을 포인터에 담아 활용한다
*/

class Transform;
class SpriteRenderer : public IRenderer
{
private:
	Transform* transform;
	D2D1_RECT_F centerRect;
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> sprite;	// TODO :: Sptie Class 만들기

public:
	// component cycle
	SpriteRenderer() 
	{ 
		RenderSystem::Get().Regist(this); 
		OutputDebugStringA("SpriteRenderer()\n");
	};
	~SpriteRenderer() override
	{ 
		RenderSystem::Get().Unregist(this);
		OutputDebugStringA("~SpriteRenderer()\n");
	}

	void OnEnable() override;
	void Update() override;
	void Render() override;
	void OnDestroy() override;

	// set
	void SetImage(const wchar_t* path);
};

