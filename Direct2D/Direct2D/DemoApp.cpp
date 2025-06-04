#include "DemoApp.h"

/// Game Init
void DemoApp::Init() {
	__super::Init();
}

/// Game Release
void DemoApp::UnInitialize() {
	__super::UnInitialize();
}

/// 윈도우 프로시저 메시지 처리
void DemoApp::MessageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	__super::MessageProc(hwnd, uMsg, wParam, lParam);

	// game에 활용할 message 처리
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	}
}