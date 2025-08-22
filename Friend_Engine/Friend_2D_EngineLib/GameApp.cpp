#include "GameApp.h"
#include "Singleton.h"

// static member init
bool GameApp::isLoop = true;

/// ������ ���ν���
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	GameApp* pThis = nullptr;

	// ������ ������
	if (uMsg == WM_NCCREATE)
	{
		// lParam�Ű��������� this ����
		CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
		pThis = reinterpret_cast<GameApp*>(cs->lpCreateParams);

		// ������ �ڵ��� GWLP_USERDATA(����� ������ ����)�� this ����
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
	}
	else {
		pThis = reinterpret_cast<GameApp*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	if (pThis)
		pThis->MessageProc(hwnd, uMsg, wParam, lParam);		// ��ü�� ��� �Լ� ȣ��

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

/// �޽��� ó��
void GameApp::MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	// ���� ���������� override
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

	// window class ����
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
	//AdjustWindowRect(&clientRect, WS_OVERLAPPEDWINDOW, FALSE);		// ������ ��� ���� ũ�� ����

	// window â ����  -> WM_NCCREATE �޽��� �߻�
	hWnd = CreateWindowEx(
		0,
		winClassName.c_str(),
		titleName.c_str(),
		WS_POPUP,		// �׵θ� ����/ WS_OVERLAPPEDWINDOW (�׵θ� ����)
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		clientRect.right - clientRect.left,
		clientRect.bottom - clientRect.top,
		NULL,
		NULL,
		hInstance,
		this  // this�� WindowProc�� ���� CREATESTRUCT ����ü Ÿ���� lParamdp �� ����ȴ�
	);

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	OutputDebugStringA("[Woo Engine] Window Create\n");


	CoInitialize(nullptr);			// com ��ü �ʱ�ȭ	
	
	// init
	Input::Init(hWnd);
	Time::Init();
	audioSystem.Init();
	renderSystem.Init(hWnd, width, height);
	resourceManager.Init();	 // rendersystem init �Ŀ� ȣ���ؾ� ��

	OutputDebugStringA("[Woo Engine] System Init\n");
}

/// Update
void GameApp::Update()
{
	Input::Update();
	Time::Update();
	InvokeSystem::Update();
	
	sceneManager.Update();
	scriptSystem.Update();
	animatorSystem.Update();
	transformSystem.Update();

	uiSystem.Update();
	renderSystem.Update();
	audioSystem.Update();

	scriptSystem.LateUpdate();
	cameraSystem.Update();
}

/// Fixed Update
void GameApp::FixedUpdate()
{
	// ���� ���� update ����
	scriptSystem.FixedUpdate();
	physicsSystem.FixedUpdate();
	colliderSystem.FixedUpdate();
}

/// Render
void GameApp::Render()
{
	renderSystem.Render();
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
				OutputDebugStringA("[Woo Engine] WM_QUIT!\n");
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// physics update -> fixed udpate
		accumulator += Time::GetDeltaTime();
		while (accumulator >= fixedDeltaTime)
		{
			FixedUpdate();
			accumulator -= fixedDeltaTime;
		}

		// update
		Update();
		Render();
	}
}

/// Release
void GameApp::UnInit()
{
	sceneManager.UnInit();
	audioSystem.UnInit();
	renderSystem.UnInit();   
	resourceManager.UnInit();
	CoUninitialize();			 // com ��ü ����

	OutputDebugStringA("[Woo Engine] GameApp Release\n");
}
