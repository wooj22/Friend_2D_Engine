#pragma once
#include <assert.h>
#include <windows.h>     // Win32 API
#include <wrl.h>         // ComPtr 스마트 포인터
#include <d3d11.h>       // Direct3D
#include <d2d1_3.h>      // Direct2D
#include <dxgi1_6.h>     // DXGI
#include <wincodec.h>    // WIC 
#include "Singleton.h"
#include "IRenderer.h"
#include <vector>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib,"windowscodecs.lib")
using namespace Microsoft::WRL;    // Microsoft::WRL::ComPtr<T>
using namespace std;

class SpriteRenderer;
class RenderSystem : public Singleton<RenderSystem>
{
private:
	// renderList
	vector<IRenderer*> components;		// render 객체들

	// window
	HWND hwnd;
	int width;
	int height;

public :
	// Direct2D Engine
	ComPtr<ID3D11Device> d3dDevice;				    // D3D Device (gpu 연결)
	ComPtr<IDXGISwapChain1> swapChain;	            // SwapChain (더블버퍼링)
	ComPtr<ID2D1DeviceContext7> renderTarget;       // D2D Device Context (그리기)
	ComPtr<ID2D1Bitmap1> backBufferBitmap;	  	    // 화면 출력용 D2D Bitmap (그릴 대상)
	ComPtr<IWICImagingFactory> wicImagingFactory;   // WIC Imaging Factory (이미지 로딩)

	// componenet
	void Regist(IRenderer* component);
	void Unregist(IRenderer* component);

	// component system
	void Init(HWND hwnd, int width, int height);
	void Update();
	void Render();
	void UnInit();			

	// functions
	HRESULT CreateBitmapFromFile(const wchar_t* path, ID2D1Bitmap1** outBitmap);	// 이미지 로드
};
