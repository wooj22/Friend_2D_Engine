#include "RenderSystem.h"
#include "SpriteRenderer.h"
#include "WorldTextRenderer.h"
#include "ImageRenderer.h"
#include "ScreenTextRenderer.h"

/// Component 등록
void RenderSystem::Regist(IRenderer* component)
{
	components.push_back(component);
}

/// Component 등록 해제
void RenderSystem::Unregist(IRenderer* component)
{
	for (auto it = components.begin(); it != components.end(); ++it) {
		if (*it == component) {
			components.erase(it);
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

	// Create WIC Factory
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory,
		NULL, CLSCTX_INPROC_SERVER,
		__uuidof(wicImagingFactory),
		(void**)wicImagingFactory.GetAddressOf());

	// DirectWrite 팩터리를 만듭니다.
	DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(dWriteFactory),
		reinterpret_cast<IUnknown**>(dWriteFactory.GetAddressOf()));

	assert(SUCCEEDED(hr));
}

void RenderSystem::Update()
{
	for (auto it = components.begin(); it != components.end(); ++it)
	{
		(*it)->Update();
	}
}

/// Render
void RenderSystem::Render() 
{
	renderTarget->BeginDraw();
	renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
	renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	// GameObject Render()
	for (IRenderer* component : components)
	{
		if (component && component->rendertype == RenderType::GameObject)
			component->Render();
	}

	// UI Render()
	for (IRenderer* component : components)
	{
		if (component && component->rendertype == RenderType::UI)
			component->Render();
	}

	renderTarget->EndDraw();
	swapChain->Present(1, 0);
}

/// UnInit
void RenderSystem::UnInit()
{
	// d2d
	d3dDevice = nullptr;
	swapChain = nullptr;
	renderTarget = nullptr;
	backBufferBitmap = nullptr;
	wicImagingFactory = nullptr;
}

/// Image Loading Function
HRESULT RenderSystem::CreateBitmapFromFile(const wchar_t* path, ID2D1Bitmap1** outBitmap)
{
	ComPtr<IWICBitmapDecoder>     decoder;
	ComPtr<IWICBitmapFrameDecode> frame;
	ComPtr<IWICFormatConverter>   converter;

	// ① 디코더 생성
	HRESULT hr = wicImagingFactory->CreateDecoderFromFilename(
		path, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder);
	if (FAILED(hr)) return hr;

	// ② 첫 프레임 얻기
	hr = decoder->GetFrame(0, &frame);
	if (FAILED(hr)) return hr;

	// ③ 포맷 변환기 생성
	hr = wicImagingFactory->CreateFormatConverter(&converter);
	if (FAILED(hr)) return hr;

	// ④ GUID_WICPixelFormat32bppPBGRA로 변환
	hr = converter->Initialize(
		frame.Get(),
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom
	);
	if (FAILED(hr)) return hr;

	// ⑤ Direct2D 비트맵 속성 (premultiplied alpha, B8G8R8A8_UNORM)
	D2D1_BITMAP_PROPERTIES1 bmpProps = D2D1::BitmapProperties1(
		D2D1_BITMAP_OPTIONS_NONE,
		D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)
	);

	// ⑥ DeviceContext에서 WIC 비트맵으로부터 D2D1Bitmap1 생성
	hr = renderTarget->CreateBitmapFromWicBitmap(converter.Get(), &bmpProps, outBitmap);
	return hr;
}