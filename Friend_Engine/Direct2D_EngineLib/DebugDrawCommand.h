#pragma once
#include <d2d1.h>

// debug type
enum class DebugDrawType
{
	Rect, Circle, Line
};

// debug draw command
// render system�� debug draw�� �����ϴ� ��ü
struct DebugDrawCommand
{
	DebugDrawType type;					// draw type
	D2D1_MATRIX_3X2_F transform;		// transform
	float strokeWidth;					// �� ����

	// union : ���� ����� ���� �޸� ������ ����
	union
	{
		D2D1_RECT_F rect;
		D2D1_ELLIPSE ellipse;
		struct { D2D1_POINT_2F start, end; } line;
	};
};