#include "DemoApp.h"

/// Game Init
void DemoApp::Init()
{
	__super::Init();

	// image load
	d2dRenderManager.CreateBitmapFromFile(L"../Resource/Sun.png", sunImage.image.GetAddressOf());
	d2dRenderManager.CreateBitmapFromFile(L"../Resource/Earth.png", earthImage.image.GetAddressOf());
	d2dRenderManager.CreateBitmapFromFile(L"../Resource/Moon.png", moonImage.image.GetAddressOf());

	// 축 보정
	sunImage.AxisCoreection();
	earthImage.AxisCoreection();
	moonImage.AxisCoreection();

	// 부모 지정
	earthImage.transform.SetParent(&sunImage.transform);
	moonImage.transform.SetParent(&earthImage.transform);

	// 위치 초기화
	earthImage.transform.SetPosition(200, 0);
	moonImage.transform.SetPosition(50, 0);
}

/// Game Update
void DemoApp::Update()
{
	__super::Update();

	// image transform update
	
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