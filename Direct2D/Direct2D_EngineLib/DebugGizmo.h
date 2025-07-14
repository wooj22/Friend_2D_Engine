#pragma once
#include <d2d1_3.h>
#include <wrl.h>
#include "Singleton.h"
#include "RenderSystem.h"

struct GizmoRect
{
    D2D1::Matrix3x2F transform;
    D2D1_RECT_F rect;
};

// DebugGizmo 유틸리티
class DebugGizmo : public Singleton<DebugGizmo>
{
private:
	ComPtr<ID2D1DeviceContext> renderTarget;
    ComPtr<ID2D1SolidColorBrush> brush;
    D2D1_COLOR_F color = D2D1::ColorF(D2D1::ColorF::Red);

    std::vector<GizmoRect> rects;

public:
    void Init(ComPtr<ID2D1DeviceContext> target)
    {
        renderTarget = target;
        renderTarget->CreateSolidColorBrush(color, brush.GetAddressOf());
    }

    void AddGizmoRect(const D2D1::Matrix3x2F& transformMatrix, const D2D1_RECT_F& localRect)
    {
        rects.push_back({ transformMatrix, localRect });
    }

    /*void DrawLine(const D2D1_POINT_2F& p1, const D2D1_POINT_2F& p2, float thickness = 1.0f)
    {
        renderTarget->DrawLine(p1, p2, brush.Get(), thickness);
    }

    void DrawCircle(const D2D1_POINT_2F& center, float radius, float thickness = 1.0f)
    {
        D2D1_ELLIPSE ellipse = { center, radius, radius };
        renderTarget->DrawEllipse(ellipse, brush.Get(), thickness);
    }*/

    void DrawAll()
    {
        if (!renderTarget || !brush) return;

        for (auto& gizmo : rects)
        {
            // 4 꼭짓점에 transformMatrix 적용
            D2D1_POINT_2F points[4] = {
                {gizmo.rect.left, gizmo.rect.top},
                {gizmo.rect.right, gizmo.rect.top},
                {gizmo.rect.right, gizmo.rect.bottom},
                {gizmo.rect.left, gizmo.rect.bottom}
            };

            for (int i = 0; i < 4; ++i)
                points[i] = gizmo.transform.TransformPoint(points[i]);

            // 4 선으로 사각형 그리기
            for (int i = 0; i < 4; ++i)
            {
                renderTarget->DrawLine(points[i], points[(i + 1) % 4], brush.Get(), 1.0f);
            }
        }

        rects.clear();
    }
};

