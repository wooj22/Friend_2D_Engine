#pragma once
#include <d2d1_1.h>
#include <string>
#include <iostream>
#include "Texture2D.h"

/* [Sprite]
* Texture2D의 Rect와 메타 데이터를 담은 그래픽 객체.
* 비트맵 로드 비용을 줄인다.
* SpriteRenderer, ImageRenderer에서 렌더할 리소스로 사용되며 ResourceManager에서 관리된다.
*/

class Sprite
{
public:
	std::string name;
	D2D1_SIZE_F size = { 0, 0 };
	D2D1_RECT_F sourceRect = { 0, 0, 0, 0 };
	D2D1_POINT_2F pivot = { 0.5f, 0.5f };
	std::shared_ptr<Texture2D> texture = nullptr;

public:
    // texture 전체영역을 sprite로 생성
    Sprite(std::shared_ptr<Texture2D> tex, std::string spriteName)
    {
        texture = tex;
        name = spriteName;
        size = tex->size;
        sourceRect = { 0, 0, tex->size.width, tex->size.height };
    }

    // texture의 일부영역을 sprite로 생성
    Sprite(std::shared_ptr<Texture2D> tex, std::string spriteName, D2D1_RECT_F rect, D2D1_POINT_2F pivotPoint)
    {
        texture = tex;
        name = spriteName;
        size = tex->size;
        sourceRect = rect;
        pivot = pivotPoint;

        size.width = rect.right - rect.left;
        size.height = rect.bottom - rect.top;
    }
};

