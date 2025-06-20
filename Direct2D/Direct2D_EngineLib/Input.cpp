#include "Input.h"

HWND Input::hWnd = nullptr;
POINT Input::mouseClient = { 0, 0 };
SHORT Input::prevState[256] = { 0 };
SHORT Input::currState[256] = { 0 };

void Input::Init(HWND hwnd)
{
    hWnd = hwnd;
    GetCursorPos(&mouseClient);
    ScreenToClient(hWnd, &mouseClient);

    // 초기 키 상태
    for (int i = 0; i < 256; ++i)
        currState[i] = GetAsyncKeyState(i);
}

void Input::Update()
{
    memcpy(prevState, currState, sizeof(SHORT) * 256);

    for (int i = 0; i < 256; ++i)
        currState[i] = GetAsyncKeyState(i);

    GetCursorPos(&mouseClient);
    ScreenToClient(hWnd, &mouseClient);
}

bool Input::GetKey(int vKey)
{
    return (currState[vKey] & 0x8000) != 0;
}

bool Input::GetKeyDown(int vKey)
{
    return !(prevState[vKey] & 0x8000) && (currState[vKey] & 0x8000);
}

bool Input::GetKeyUp(int vKey)
{
    return (prevState[vKey] & 0x8000) && !(currState[vKey] & 0x8000);
}

POINT Input::GetMousePosition()
{
    return mouseClient;
}
