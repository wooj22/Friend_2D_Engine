#pragma once
#include <wrl/client.h> 
#include <d2d1_1.h>

/* [Texture2D]
* 2D bitmap 리소스 하나를 가지는 클래스
* Sprite의 멤버로 등록되어 SpriteRenderer, ImageRenderer에서 리소스로 사용되며
* ResourceManager에서 관리된다. (TODO :: Sprite 클래스 만들기)
*/

class Texture2D
{
public:
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> texture2D;
};

