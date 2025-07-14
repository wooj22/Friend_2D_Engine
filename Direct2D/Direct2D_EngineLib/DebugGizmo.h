#pragma once
#include <d2d1_3.h>
#include <wrl.h>
#include "Singleton.h"
#include "RenderSystem.h"

// DebugGizmo 유틸리티
// renderTarget은 rendersystem꺼 뺏어쓰는중 ㅎ

class DebugGizmo : public Singleton<DebugGizmo>
{
private:
	ComPtr<ID2D1DeviceContext> renderTarget;
    ComPtr<ID2D1SolidColorBrush> brush;
    D2D1_COLOR_F color = D2D1::ColorF(D2D1::ColorF::Red);

public:
    void Init(ComPtr<ID2D1DeviceContext> target)
    {
        renderTarget = target;
        renderTarget->CreateSolidColorBrush(color, brush.GetAddressOf());
    }

    void DrawRect(const D2D1_RECT_F& rect, float thickness = 1.0f)
    {
        renderTarget->DrawRectangle(rect, brush.Get(), thickness);
    }

    void DrawLine(const D2D1_POINT_2F& p1, const D2D1_POINT_2F& p2, float thickness = 1.0f)
    {
        renderTarget->DrawLine(p1, p2, brush.Get(), thickness);
    }

    void DrawCircle(const D2D1_POINT_2F& center, float radius, float thickness = 1.0f)
    {
        D2D1_ELLIPSE ellipse = { center, radius, radius };
        renderTarget->DrawEllipse(ellipse, brush.Get(), thickness);
    }
};

