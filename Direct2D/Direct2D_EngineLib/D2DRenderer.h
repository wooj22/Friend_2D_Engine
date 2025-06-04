#pragma once
#include <assert.h>
#include <windows.h>     // Win32 API
#include <wrl.h>         // ComPtr 스마트 포인터
#include <d3d11.h>       // Direct3D
#include <d2d1_3.h>      // Direct2D
#include <dxgi1_6.h>     // DXGI
#include <wincodec.h>    // WIC 
#include "Singleton.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib,"windowscodecs.lib")
using namespace Microsoft::WRL;    // Microsoft::WRL::ComPtr<T>


class D2DRenderer : public Singleton<D2DRenderer>
{
public :
	// window
	HWND hwnd;
	int width;
	int height;

	// Direct2D Engine
	ComPtr<ID3D11Device> g_d3dDevice;				  // D3D Device
	ComPtr<IDXGISwapChain1> g_dxgiSwapChain;	      // SwapChain
	ComPtr<ID2D1DeviceContext7> g_d2dDeviceContext;   // D2D Device Context
	ComPtr<ID2D1Bitmap1> g_d2dBitmapTarget;	  	      // 화면 출력용 D2D Bitmap Target

	// ImageDraw
	ComPtr<IWICImagingFactory> g_wicImagingFactory;   // WIC Imaging Factory, 이미지 로딩용
	ComPtr<ID2D1Bitmap1> g_d2dBitmapFromFile;	      // 로드된 이미지 비트맵 저장용

	void Init(HWND hwnd, int width, int height);
	void UnInit() {};							      // 스마트 포인터를 사용하므로 따로 해제 x
	HRESULT CreateBitmapFromFile(const wchar_t* path, ID2D1Bitmap1** outBitmap);
};
