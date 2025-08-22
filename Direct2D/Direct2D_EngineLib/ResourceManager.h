#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <memory>
#include <filesystem>
#include <iomanip>
#include <conio.h> 
#include <queue>

#include <d3d11.h>
#include <d2d1_3.h>
#include <wrl.h>
#include <wincodec.h>
#include <dxgi1_6.h>
#include <psapi.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "psapi.lib")
#pragma comment(lib,"windowscodecs.lib")

#include "Singleton.h"

using namespace std;
using namespace Microsoft::WRL;

/* [ResourceManager]
* ���� �ڿ��� �ߺ����� �޸𸮿� �ε����� �ʵ��� �ؽ����̺�� �����ϴ� Ŭ����
* key������ weak_ptr�� ���ο��� ������ �ϸ�, �ܺ� ��û�� ������ ���
* shared_ptr�� ��ȯ�Ͽ� �����Ѵ�. (���� ��쿡�� ���� ����)
*/

class Texture2D;
class Sprite;
class AudioClip;
class ResourceManager : public Singleton<ResourceManager>
{
private:
	unordered_map<string, weak_ptr<Texture2D>> map_texture2D;		// texture file path
	unordered_map<string, weak_ptr<Sprite>> map_sprite;				// sprite name
	//unordered_map<string, weak_ptr<AnimationClip>> map_animationClip;
	unordered_map<string, weak_ptr<AudioClip>> map_AudioClip;	    // audioClip file path

private:
	// d2d
	ComPtr<IWICImagingFactory> wicImagingFactory;
	ComPtr<IDXGIDevice3> dxgiDevice; 
	ComPtr<IDXGIAdapter3> dxgiAdapter;
	
public:
	HRESULT Init();
	void UnInit();
	wstring FormatBytes(UINT64 bytes);
	wstring GetMemoryUsageWString();
	void PrintMemoryUsage();
	void Trim();

public:
	shared_ptr<Texture2D> CreateTexture2D(string filePath);
	shared_ptr<Sprite> CreateSprite(shared_ptr<Texture2D> texture, string spriteName);
	shared_ptr<Sprite> CreateSprite(shared_ptr<Texture2D> texture, string spriteName, D2D1_RECT_F rect, D2D1_POINT_2F pivotPoint = { 0.5f, 0.5f });
	shared_ptr<AudioClip> CreateAudioClip(string filePath);
};
