#include "RenderSystem.h"
#include "SpriteRenderer.h"
#include "WorldTextRenderer.h"
#include "ImageRenderer.h"
#include "ScreenTextRenderer.h"
#include "ColliderSystem.h"
#include <algorithm>

/// Component 등록
void RenderSystem::Regist(IRenderer* component)
{
	if (component->rendertype == RenderType::GameObject)
	{
		game_renderers.push_back(component);
	}
	else if (component->rendertype == RenderType::UI)
	{
		ui_renderers.push_back(component);
	}
}

/// Component 등록 해제
void RenderSystem::Unregist(IRenderer* component)
{
	for (auto it = game_renderers.begin(); it != game_renderers.end(); ++it) {
		if (*it == component) {
			game_renderers.erase(it);
			return;
		}
	}
	for (auto it = ui_renderers.begin(); it != ui_renderers.end(); ++it) {
		if (*it == component) {
			ui_renderers.erase(it);
			return;
		}
	}
}

/// Init
void RenderSystem::Init(HWND hwnd, int width, int height) 
{
	this->hwnd = hwnd;
	this->width = width;
	this->height = height;

	// D3D11 Device
	D3D_FEATURE_LEVEL featureLevel;
	D3D_FEATURE_LEVEL levels[] = { D3D_FEATURE_LEVEL_11_0 };
	D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
		D3D11_CREATE_DEVICE_BGRA_SUPPORT, levels, 1,
		D3D11_SDK_VERSION, d3dDevice.GetAddressOf(), &featureLevel, nullptr);

	// D2D Factory, Device
	ComPtr<ID2D1Factory8> d2dFactory;		// D2D Factory : Direct2D 객체를 생성하는 팩토리
	D2D1_FACTORY_OPTIONS options = {};
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, options, d2dFactory.GetAddressOf());

	ComPtr<IDXGIDevice> dxgiDevice;			// DXGI Device
	d3dDevice.As(&dxgiDevice);
	ComPtr<ID2D1Device7> d2dDevice;			// D2D Device
	d2dFactory->CreateDevice((dxgiDevice.Get()), d2dDevice.GetAddressOf());

	// D2D Device context
	d2dDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, renderTarget.GetAddressOf());

	// DXGI Factory
	ComPtr<IDXGIFactory7> dxgiFactory;
	CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));

	// SwapChain
	DXGI_SWAP_CHAIN_DESC1 scDesc = {};
	scDesc.Width = width;
	scDesc.Height = height;
	scDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	scDesc.SampleDesc.Count = 1;
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDesc.BufferCount = 2;
	scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	dxgiFactory->CreateSwapChainForHwnd(d3dDevice.Get(), hwnd, &scDesc, nullptr, nullptr, swapChain.GetAddressOf());

	// 백버퍼를 타겟으로 설정 -> DeginDraw(), EndDraw() 가능
	ComPtr<IDXGISurface> backBuffer;
	swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));

	D2D1_BITMAP_PROPERTIES1 bmpProps = D2D1::BitmapProperties1(		// 버퍼를 D2D용 Bitmap으로 감쌈
		D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
		D2D1::PixelFormat(scDesc.Format, D2D1_ALPHA_MODE_PREMULTIPLIED)
	);
	renderTarget->CreateBitmapFromDxgiSurface(backBuffer.Get(), &bmpProps, backBufferBitmap.GetAddressOf());
	renderTarget->SetTarget(backBufferBitmap.Get());

	// DirectWrite 팩터리를 만듭니다.
	DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(dWriteFactory),
		reinterpret_cast<IUnknown**>(dWriteFactory.GetAddressOf()));

	// debug
	renderTarget->CreateSolidColorBrush(debug_color, &debug_brush);
}

void RenderSystem::Update()
{
	// GameObject Update()
	for (IRenderer* renderer : game_renderers)
	{
		renderer->Update();
	}

	// UI Update()
	for (IRenderer* renderer : ui_renderers)
	{
		renderer->Update();
	}
}

/// Render
void RenderSystem::Render() 
{
	renderTarget->BeginDraw();
	renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	// layer sort
	sort(game_renderers.begin(), game_renderers.end(),
		[](IRenderer* a, IRenderer* b) { return a->layer < b->layer; });

	sort(ui_renderers.begin(), ui_renderers.end(),
		[](IRenderer* a, IRenderer* b) { return a->layer < b->layer; });

	// GameObject Render()
	for (IRenderer* renderer : game_renderers)
	{
		renderer->Render();
	}

	// UI Render()
	for (IRenderer* renderer : ui_renderers)
	{
		renderer->Render();
	}

	// collider draw
	ColliderSystem::Get().DebugColliderDraw();

	renderTarget->EndDraw();
	swapChain->Present(1, 0);
}

/// UnInit
void RenderSystem::UnInit()
{
	// d2d
	d3dDevice.Reset();
	swapChain.Reset();
	renderTarget.Reset();
	backBufferBitmap.Reset();
	dWriteFactory.Reset();
}


// debug
void RenderSystem::DrawRect(const D2D1_RECT_F& rect, const D2D1_MATRIX_3X2_F& transform, float strokeWidth)
{
	renderTarget->SetTransform(transform);
	renderTarget->DrawRectangle(rect, debug_brush.Get(), strokeWidth);
}

void RenderSystem::DrawCircle(const D2D1_ELLIPSE& ellipse, const D2D1_MATRIX_3X2_F& transform, float strokeWidth)
{
	renderTarget->SetTransform(transform);
	renderTarget->DrawEllipse(ellipse, debug_brush.Get(), strokeWidth);
	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void RenderSystem::DrawLine(const D2D1_POINT_2F& start, const D2D1_POINT_2F& end, const D2D1_MATRIX_3X2_F& transform, float strokeWidth)
{
	renderTarget->SetTransform(transform);
	renderTarget->DrawLine(start, end, debug_brush.Get(), strokeWidth);
	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}