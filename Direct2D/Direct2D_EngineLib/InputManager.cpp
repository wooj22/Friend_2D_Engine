#include "InputManager.h"

void InputManager::Init(HWND hWnd)
{
	this->hWnd = hWnd;
}

void InputManager::Update()
{
	::GetCursorPos(&mouseClient);
	::ScreenToClient(hWnd, &mouseClient);

	memcpy_s(prevState, sizeof(prevState), currState, sizeof(currState));

	for (int i = 0; i < 256; i++) {
		currState[i] = GetAsyncKeyState(i);
	}
}

bool InputManager::GetKey(int vKey)
{
	return (currState[vKey] & 0x8000) != 0;
}

bool InputManager::GetKeyDown(int vKey)
{
	return (!(prevState[vKey] & 0x8000) && (currState[vKey] & 0x8000));
}

bool InputManager::GetKeyUP(int vKey)
{
	return ((prevState[vKey] & 0x8000) && !(currState[vKey] & 0x8000));
}