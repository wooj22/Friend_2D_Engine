#pragma once
#include <d2d1_1.h>
#include <string>
#include <iostream>
#include "Texture2D.h"

/* [Sprite]
* Texture2D�� Rect�� ��Ÿ �����͸� ���� �׷��� ��ü.
* Texuture �ϳ��� Sprite�� �������� �ְ�, �Ϻ� ������ Sprite�� �����Ͽ� ��Ʈ�� �ε� ����� ���� ���� �ִ�.
* ResourceManager���� �����ڿ����� �����Ǹ� name�� key�̱� ������ �����Ҷ� ��� �ٸ� �̸��� �������־�� �Ѵ�.
* SpriteRenderer, ImageRenderer���� ������ ���ҽ��� ���Ǹ� 
* SpriteRenderer������ Sprite�� ��Ÿ�����ʹ�� render������
* ImagerRenderer������ onwer ���ӿ�����Ʈ�� RectTransform�� ���߾� �������ȴ�.
*/

class Sprite
{
public:
	std::string name;                               // sprite name (���ҽ��Ŵ����� Ű�� ���)
	D2D1_SIZE_F size = { 0, 0 };                    // sprite width, height
	D2D1_RECT_F sourceRect = { 0, 0, 0, 0 };        // texture���� �ڸ� ����
	D2D1_POINT_2F pivot = { 0.5f, 0.5f };           // {0,0} left, down
	std::shared_ptr<Texture2D> texture = nullptr;   // Texture2D

public:
    // texture ��ü������ sprite�� ����
    Sprite(std::shared_ptr<Texture2D> tex, std::string spriteName)
    {
        texture = tex;
        name = spriteName;
        size = tex->size;
        sourceRect = { 0, 0, tex->size.width, tex->size.height };
    }

    // texture�� �Ϻο����� sprite�� ����
    Sprite(std::shared_ptr<Texture2D> tex, std::string spriteName, D2D1_RECT_F rect, D2D1_POINT_2F pivotPoint)
    {
        texture = tex;
        name = spriteName;
        sourceRect = rect;
        pivot = pivotPoint;

        size.width = rect.right - rect.left;
        size.height = rect.bottom - rect.top;

        // debug
        //OutputDebugStringA(("Sprite sourceRect: " + std::to_string(sourceRect.left) + ", " + std::to_string(sourceRect.top) + ", " + std::to_string(sourceRect.right) + ", " + std::to_string(sourceRect.bottom) + "\n").c_str());
        //OutputDebugStringA(("Sprite size: " + std::to_string(size.width) + "x" + std::to_string(size.height) + "\n").c_str());
    }
};