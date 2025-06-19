#pragma once
#include <wrl/client.h> 
#include <d2d1_1.h>
#include "RenderSystem.h"
#include "IRenderer.h"

/* Sprite Renderer Conponent */
class Transform;
class SpriteRenderer : public IRenderer
{
private:
	D2D1_RECT_F centerRect;
	Transform* transform;

public:
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> sprite;

	SpriteRenderer() { RenderSystem::Get().Regist(this); };
	~SpriteRenderer() override { RenderSystem::Get().Unregist(this); }

	void OnEnable() override;
	void Update() override;
	void Render() override;
	void OnDestroy() override;

	void SetImage(const wchar_t* path);
};

