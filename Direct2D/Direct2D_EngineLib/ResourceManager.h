#pragma once
#include <d3d11.h>
#include <d2d1_3.h>
#include <wrl.h>
#include <wincodec.h>
#include <unordered_map>
#include <string>
#include <memory>
#include <filesystem>
#include <iostream>
#include "Singleton.h"

using namespace std;
using namespace Microsoft::WRL;

/* [ResourceManager]
* 공유 자원을 중복으로 메모리에 로드하지 않도록 해시테이블로 관리하는 클래스
* filePath를 key값으로 하여 weak_ptr로 내부에서 관리를 하며, 외부 요청이 들어왔을 경우
* shared_ptr로 변환하여 리턴한다. (없을 경우에만 새로 생성)
*/

class Texture2D;
class ResourceManager : public Singleton<ResourceManager>
{
private:
	unordered_map<string, weak_ptr<Texture2D>> map_texture2D;
    ComPtr<IWICImagingFactory> wicImagingFactory;

public:
	shared_ptr<Texture2D> CreateTexture2D(string filePath);
};
