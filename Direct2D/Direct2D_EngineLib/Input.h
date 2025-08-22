﻿#pragma once
#include <Windows.h>
#include "Vector2.h"

class Input
{
private:
    static HWND hWnd;
    static POINT mouseClient;
    static SHORT prevState[256];
    static SHORT currState[256];

    static float horizontalAxis;
    static float verticalAxis;

public:
    static void Init(HWND hwnd);
    static void Update();

    static bool GetKey(int vKey);
    static bool GetKeyDown(int vKey);
    static bool GetKeyUp(int vKey);

	static bool GetMouseButton(int button);
    static bool GetMouseButtonDown(int button);
	static bool GetMouseButtonUp(int button);

    static float GetAxisHorizontal();
    static float GetAxisVertical();

	static Vector2 GetMouseScreenPosition_D2D();        // screen position (UI - d2d style)
    static Vector2 GetMouseScreenPosition();            // screen position (UI - unity style)
};