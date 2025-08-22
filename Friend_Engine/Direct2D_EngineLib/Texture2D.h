#pragma once
#include <wrl/client.h> 
#include <d2d1_1.h>
#include <string>

/* [Texture2D]
* 2D bitmap ���ҽ� �ϳ��� ������ Ŭ����
* Sprite�� ����� ��ϵǾ� SpriteRenderer, ImageRenderer���� render ��� ��ü�� ���ȴ�.
* Texture�� �ϳ��� Sprite�� �� ���� �ְ�, ���� Sprite�� �ɰ��� ���� �ִ�.
* ResourceManager���� �����Ǿ� ���� Sprite�� ������ Textrue�� ������ �ʰ� �ڿ��� ������ �� �ְԲ� �Ѵ�.
*/

class Texture2D
{
public:
	std::string filePath;								// file path
	D2D1_SIZE_F size;									// width, height
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> texture2D;		// bitmap image
};