#include "GameApp.h"
#include "Singleton.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	GameApp* pThis = nullptr;

	// 윈도우 생성시
	if (uMsg == WM_NCCREATE)
	{
		// lParam매개변수에서 this 추출
		CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
		pThis = reinterpret_cast<GameApp*>(cs->lpCreateParams);

		// 윈도우 핸들의 GWLP_USERDATA(사용자 데이터 공간)에 this 저장
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
	}
	else {
		pThis = reinterpret_cast<GameApp*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	if (pThis)
		pThis->MessageProc(hwnd, uMsg, wParam, lParam);		// 객체의 멤버 함수 호출

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

/// 메시지 처리
void GameApp::MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	// 게임 콘텐츠에서 override
}


/// Init
void GameApp::Init()
{
	// module path save
	char szPath[MAX_PATH] = { 0, };
	GetModuleFileNameA(NULL, szPath, MAX_PATH);
	modulePath = szPath;
	OutputDebugStringA(string(string(modulePath) + string("\n")).c_str());

	// directory path save
	GetCurrentDirectoryA(MAX_PATH, szPath);
	workingPath = szPath;
	OutputDebugStringA(string(string(workingPath) + string("\n")).c_str());

	// get program handle
	hInstance = GetModuleHandle(NULL);

	// window class 정의
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WindowProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;
	wc.lpszClassName = winClassName.c_str();
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	RegisterClassEx(&wc);

	SIZE clientSize = { width, height };
	RECT clientRect = { 0, 0, clientSize.cx, clientSize.cy };
	AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, FALSE);

	// window 창 생성  -> WM_NCCREATE 메시지 발생
	hWnd = CreateWindowEx(
		0,
		winClassName.c_str(),
		titleName.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		clientRect.right - clientRect.left,
		clientRect.bottom - clientRect.top,
		NULL,
		NULL,
		hInstance,
		this  // this가 WindowProc를 통해 CREATESTRUCT 구조체 타입의 lParamdp 에 저장된다
	);

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	CoInitialize(nullptr);					// com 객체 초기화	
	d2dRenderer.Init(hWnd, width, height); // direct 2D init
}

/// Update
void GameApp::Update()
{
	
}

/// Render
void GameApp::Render()
{
	d2dRenderer.g_d2dDeviceContext->BeginDraw();		// 그리기 시작
	d2dRenderer.g_d2dDeviceContext->Clear(D2D1::ColorF(D2D1::ColorF::DarkSlateBlue));		// 배경색

	D2D1_SIZE_F size;
	d2dRenderer.g_d2dDeviceContext->SetTransform(D2D1::Matrix3x2F::Identity()); // Render 위치 기본 sest

	//1. 0,0 위치에 비트맵 전체영역 그린다. (변환은 초기화)
	d2dRenderer.g_d2dDeviceContext->DrawBitmap(d2dRenderer.g_d2dBitmapFromFile.Get());

	//2. DestPos(화면 위치) 설정과 SrcPos(비트맵 위치)로 그리기
	D2D1_VECTOR_2F DestPos{ 0,0 }, SrcPos{ 0,0 }; // 화면 위치, 비트맵 위치
	size = { 0,0 };	//	그릴 크기
	D2D1_RECT_F DestRect{ 0,0,0,0 }, SrcRect{ 0,0,0,0 }; // 화면 영역, 비트맵 영역
	D2D1_MATRIX_3X2_F transform;	// 변환 행렬

	// 화면 위치를 지정하고, 비트맵 크기 만큼 DestRect을 설정하여 비트맵 그리기
	DestPos = { 100,0 };
	size = d2dRenderer.g_d2dBitmapFromFile->GetSize();
	DestRect = { DestPos.x , DestPos.y, DestPos.x + size.width - 1 ,DestPos.y + size.height - 1 };
	d2dRenderer.g_d2dDeviceContext->DrawBitmap(d2dRenderer.g_d2dBitmapFromFile.Get(), DestRect);

	//3. DestRect(그릴 영역) 설정과 SrcRect(비트맵 일부 영역)로 그리기
	size = { 200,200 };
	DestPos = { 100,100 };
	DestRect = { DestPos.x , DestPos.y, DestPos.x + size.width - 1 ,DestPos.y + size.height - 1 };

	SrcPos = { 0,0 }; // 비트맵의 일부 영역을 그리기 위해 SrcPos 설정
	SrcRect = { SrcPos.x,SrcPos.y, SrcPos.x + size.width - 1 ,SrcPos.y + size.height - 1 };
	d2dRenderer.g_d2dDeviceContext->
		DrawBitmap(d2dRenderer.g_d2dBitmapFromFile.Get(),
			DestRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &SrcRect);

	//4. 변환을 사용한 반전으로 DestRect(그릴 영역) 설정과 SrcRect(비트맵 일부 영역)로 그리기
	DestPos = { 700,100 };
	DestRect = { DestPos.x , DestPos.y, DestPos.x + size.width - 1 ,DestPos.y + size.height - 1 };

	transform = D2D1::Matrix3x2F::Scale(-1.0f, 1.0f,  // x축 반전
		D2D1::Point2F(DestPos.x, DestPos.y));         // 기준점
	d2dRenderer.g_d2dDeviceContext->SetTransform(transform);
	d2dRenderer.g_d2dDeviceContext->
		DrawBitmap(d2dRenderer.g_d2dBitmapFromFile.Get(),
			DestRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &SrcRect);

	//5. 복합변환을 사용한 반전으로 DestRect(그릴 영역) 설정과 SrcRect(비트맵 일부 영역)로 그리기
	DestPos = { 0,0 };   // 그릴 위치는 0,0으로 하고 이동변환을 사용한다.
	DestRect = { DestPos.x , DestPos.y, DestPos.x + size.width - 1 ,DestPos.y + size.height - 1 };

	transform = D2D1::Matrix3x2F::Scale(1.0f, 1.0f, D2D1::Point2F(0.0f, 0.0f)) *
		D2D1::Matrix3x2F::Rotation(90.0f, D2D1::Point2F(0.0f, 0.0f)) * // 90도 회전
		D2D1::Matrix3x2F::Translation(900.0f, 900.0f);  // 이동

	// 기준점
	d2dRenderer.g_d2dDeviceContext->SetTransform(transform);
	d2dRenderer.g_d2dDeviceContext->
		DrawBitmap(d2dRenderer.g_d2dBitmapFromFile.Get(),
			DestRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &SrcRect);

	d2dRenderer.g_d2dDeviceContext->EndDraw();
	d2dRenderer.g_dxgiSwapChain->Present(1, 0);
}

/// GameLoop
void GameApp::Loop()
{
	MSG msg = {};
	while (isLoop)
	{
		// message
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) {
				isLoop = false;
				break;
			}
				
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			
		}

		Update();
		Render();
	}
}

/// Release
void GameApp::UnInit()
{
	CoUninitialize();		// com 객체 해제
}
