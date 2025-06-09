#include "DemoApp.h"

/// Game Init
void DemoApp::Init() 
{
	__super::Init();
}

/// Game Update
void DemoApp::Update()
{
	__super::Update();
}

/// Game Render
void DemoApp::Render() 
{
	d2dRenderer.d2dDeviceContext->BeginDraw();
	d2dRenderer.d2dDeviceContext->Clear(D2D1::ColorF(D2D1::ColorF::YellowGreen));
	d2dRenderer.d2dDeviceContext->SetTransform(D2D1::Matrix3x2F::Identity());

	// 이미지 크기 얻기
	D2D1_SIZE_F bitmapSize = d2dRenderer.d2dBitmapFromFile->GetSize();

	// 현재 렌더 타겟(창)의 크기 얻기
	D2D1_SIZE_F renderTargetSize = d2dRenderer.d2dDeviceContext->GetSize();

	// 중앙 위치 계산
	float destX = (renderTargetSize.width - bitmapSize.width) / 2.0f;
	float destY = (renderTargetSize.height - bitmapSize.height) / 2.0f;

	// 중앙에 출력할 DestRect 설정
	D2D1_RECT_F destRect = {
		destX,
		destY,
		destX + bitmapSize.width,
		destY + bitmapSize.height
	};

	// 이미지 출력 (정중앙에)
	d2dRenderer.d2dDeviceContext->DrawBitmap(d2dRenderer.d2dBitmapFromFile.Get(), destRect);

	d2dRenderer.d2dDeviceContext->EndDraw();
	d2dRenderer.dxgiSwapChain->Present(1, 0);
}

/// Game Release
void DemoApp::UnInit() 
{
	__super::UnInit();
}

/// 윈도우 프로시저 메시지 처리
void DemoApp::MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	__super::MessageProc(hwnd, uMsg, wParam, lParam);

	// game에 활용할 message 처리
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	}
}