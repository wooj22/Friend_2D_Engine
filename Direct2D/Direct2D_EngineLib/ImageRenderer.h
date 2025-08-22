#pragma once
#include <wrl.h>
#include <assert.h>
#include "IRenderer.h"
#include "RenderSystem.h"
#include "Texture2D.h"
#include "Sprite.h"
#include "ResourceManager.h"
#include "iostream"

#include <d2d1_1.h>
#include <d2d1effects_2.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dxguid.lib")

/* [Image Renderer Conponent]
* <UI>�� �̹��� �� ��(sprite)�� render�� ����ϴ� component��
* ������Ʈ ������ RenderSystem�� ��ϵǾ� sprite�� �Լ� render�Ѵ�.
* sprite�� �ִٸ� sprite ���, ���ٸ� white box ĥ�Ѵ�.
* render�� �ʿ��� rectTransform�� �� ������Ʈ�� ��ϵ� ������Ʈ�� rectTransform�� �����Ϳ� ��� Ȱ���Ѵ�.
* 
* �⺻ RenderMode�� UnLint�̸� (DrawBitMap)
* ColorEffect�� Glow(blur)Effect�� ȿ���� ����Ѵٸ� RenderMode�� �ٲ��־���Ѵ�.
* Sprite�� �������� �ʰ� Box�� �׸����ִٸ� RenderMode�� ȿ���� ������� �ʴ´�.
*/

class RectTransform;
class ImageRenderer : public IRenderer
{
private:
	RectTransform* rectTransform;

public:
	shared_ptr<Sprite> sprite;				// ���� �ڿ�  
	FillType fillType = FillType::None;		// Unlit Sprite�� ����
	float fillAmount = 1.0f;				// Horizontal : ����~/ Vertical : �Ʒ�~

private:
	// Fill Box (Empty Sprite)
	ComPtr<ID2D1SolidColorBrush> brush;
	D2D1_COLOR_F baseColor = D2D1::ColorF(D2D1::ColorF::White);

private:
	// Effect
	ComPtr<ID2D1Effect> colorMatrixEffect = nullptr;
	ComPtr<ID2D1Effect> cropEffect = nullptr;
	ComPtr<ID2D1Effect> blurEffect = nullptr;

	// ColorMatrix
	ColorRGBA colorMultiplier = { 1,1,1,1 };	// User Set : R, G, B, A
	D2D1_MATRIX_5X4_F colorMatrix = {			// color matrix ���
	colorMultiplier.a, 0, 0, 0,
	0, colorMultiplier.g, 0, 0,
	0, 0, colorMultiplier.b, 0,
	0, 0, 0, colorMultiplier.a
	};

	// Saturation
	float saturation = 1.0f;

	// ��� ��ȯ ���
	float rw = 0.3086f;
	float gw = 0.6094f;
	float bw = 0.0820f;

	// Brightness (��)
	float brightnessScale = 1.0f;

	// Blur
	float blurAmmount = 15.0f;

public:
	// component cycle
	ImageRenderer() { 
		rendertype = RenderType::UI;		// ���� Ÿ�� ���� (UI)	
	};
	~ImageRenderer() override = default;

	void OnEnable_Inner() override final;
	void OnDisable_Inner() override final;
	void Update() override final;
	void Render() override final;
	void OnDestroy_Inner() override final;

public:
	// Rect Color
	void SetBaseColor(const D2D1_COLOR_F& newColor);
	D2D1_COLOR_F GetBaseColor() { return baseColor; }
	
	// Sprite Color
	void SetColor(float r, float g, float b);		
	ColorRGBA GetColor() { return colorMultiplier; };
	
	// Alpha
	void SetAlpha(float a);	
	float GetAlpha() { return colorMultiplier.a; }	
	
	// Saturation
	// 0.6 ~ 1.0
	void SetSaturation(float s);
	float GetSaturation() { return saturation; }

	// Brightness
	void SetBrightness(float scale);
	float GetBrightness() { return brightnessScale; }

public:
	// Glow (Blur)
	void SetGlowAmmount(float blur) { blurAmmount = blur; }
};

