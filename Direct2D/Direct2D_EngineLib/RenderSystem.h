#pragma once
#include <assert.h>
#include <windows.h>     // Win32 API
#include <wrl.h>         // ComPtr 스마트 포인터
#include <d3d11.h>       // Direct3D
#include <d2d1_3.h>      // Direct2D
#include <dxgi1_6.h>     // DXGI
#include <wincodec.h>    // WIC 
#include <dwrite.h>	     // Write
#include "Singleton.h"
#include "IRenderer.h"
#include <vector>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib,"windowscodecs.lib")
#pragma comment(lib,"dwrite.lib")
using namespace Microsoft::WRL;    // Microsoft::WRL::ComPtr<T>
using namespace std;

class RenderSystem : public Singleton<RenderSystem>
{
private:
	// renderList
	vector<IRenderer*> components;		// render 객체들
	vector<IRenderer*> ui_renderers;
	vector<IRenderer*> game_renderers;

	// window
	HWND hwnd;
	int width;
	int height;

public :
	// DirectX 2D Base
	ComPtr<ID3D11Device> d3dDevice;				    // D3D Device (gpu 연결)
	ComPtr<IDXGISwapChain1> swapChain;	            // SwapChain (더블버퍼링)
	ComPtr<ID2D1DeviceContext7> renderTarget;       // D2D Device Context (그리기)
	ComPtr<ID2D1Bitmap1> backBufferBitmap;	  	    // 화면 출력용 D2D Bitmap (그릴 대상)
	ComPtr<IDWriteFactory> dWriteFactory;			// Text Write Factory (텍스트 그리기)

private:
	// debug
	ComPtr<ID2D1SolidColorBrush> debug_brush;
	D2D1_COLOR_F debug_color = D2D1::ColorF(D2D1::ColorF::Red);

public:
	// componenet
	void Regist(IRenderer* component);
	void Unregist(IRenderer* component);

	// component system
	void Init(HWND hwnd, int width, int height);
	void Update();
	void Render();
	void UnInit();			

	// debug function
	void DrawRect(const D2D1_RECT_F& rect, const D2D1_MATRIX_3X2_F& transform, float strokeWidth = 0.5f);
	void DrawCircle(const D2D1_ELLIPSE& ellipse, const D2D1_MATRIX_3X2_F& transform, float strokeWidth = 0.5f);
	void DrawLine(const D2D1_POINT_2F& start, const D2D1_POINT_2F& end, const D2D1_MATRIX_3X2_F& transform, float strokeWidth = 0.5f);
};
