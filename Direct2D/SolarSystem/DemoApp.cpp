#include "DemoApp.h"

/// Game Init
void DemoApp::Init()
{
	__super::Init();

	// camera
	mainCamera.SetSize(width, height);

	// image load
	d2dRenderManager.CreateBitmapFromFile(L"../Resource/Sun.png", sun.image.GetAddressOf());
	d2dRenderManager.CreateBitmapFromFile(L"../Resource/Earth.png", earth.image.GetAddressOf());
	d2dRenderManager.CreateBitmapFromFile(L"../Resource/Moon.png", moon.image.GetAddressOf());

	// 축 보정
	sun.AxisCoreection();
	earth.AxisCoreection();
	moon.AxisCoreection();

	// 부모 지정
	earth.transform.SetParent(&sun.transform);
	moon.transform.SetParent(&earth.transform);

	// 초기화
	sun.transform.SetPosition(50, 0);
	earth.transform.SetPosition(200, 0);
	moon.transform.SetPosition(50, 0);
}

/// Game Update
void DemoApp::Update()
{
	__super::Update();

	// image transform update
	sun.transform.AddRotation(-0.5f);
	earth.transform.AddRotation(-0.2f);
	moon.transform.AddRotation(-1);
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