#pragma once
#include <windows.h>
#include "Singleton.h"

class InputManager : public Singleton<InputManager>
{
private:
	HWND hWnd;
	POINT mouseClient;
	SHORT prevState[256] = { 0 };
	SHORT currState[256] = { 0 };

public:
	InputManager() = default;
	~InputManager() override = default;

	void Init(HWND hWnd);
	void Update();
	void Release() {};

	bool GetKey(int vKey);
	bool GetKeyDown(int vKey);
	bool GetKeyUP(int vKey);

	friend class Singleton<InputManager>;
};