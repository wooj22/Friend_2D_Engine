#include "ResourceManager.h"
#include "RenderSystem.h"
#include "Texture2D.h"
#include "Sprite.h"
#include "AudioClip.h"

/// ResourceManager Init
HRESULT ResourceManager::Init()
{
    HRESULT hr;

    // WIC Imaging Factory ����
    hr = CoCreateInstance(
        CLSID_WICImagingFactory,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(wicImagingFactory.GetAddressOf())
    );
    if (FAILED(hr))
        return hr;

    // RenderSystem���� D3D11Device ��������
    ComPtr<ID3D11Device> d3dDevice = RenderSystem::Get().d3dDevice;
    if (!d3dDevice)
        return E_FAIL;

    // IDXGIDevice �������̽� ���
    ComPtr<IDXGIDevice> dxgiDeviceBase;
    hr = d3dDevice->QueryInterface(dxgiDeviceBase.GetAddressOf());
    if (FAILED(hr))
        return hr;

    // IDXGIDeviceBase -> IDXGIDevice3 ��ȯ
    hr = dxgiDeviceBase.As(&dxgiDevice);
    if (FAILED(hr))
        return hr;

    // IDXGIAdapter ���
    ComPtr<IDXGIAdapter> dxgiAdapterBase;
    hr = dxgiDevice->GetAdapter(dxgiAdapterBase.GetAddressOf());
    if (FAILED(hr))
        return hr;

    // IDXGIAdapter -> IDXGIAdapter3 ��ȯ
    hr = dxgiAdapterBase.As(&dxgiAdapter);
    if (FAILED(hr))
        return hr;

    return S_OK;
}

void ResourceManager::UnInit() {
    wicImagingFactory.Reset();
    dxgiDevice.Reset();
    dxgiAdapter.Reset();
}

/// Format bytes to human-readable string
wstring ResourceManager::FormatBytes(UINT64 bytes) {
    constexpr double KB = 1024.0;
    constexpr double MB = KB * 1024.0;
    constexpr double GB = MB * 1024.0;

    std::wostringstream oss;
    oss << std::fixed << std::setprecision(2);

    if (bytes >= static_cast<UINT64>(GB))
        oss << (bytes / GB) << L" GB";
    else if (bytes >= static_cast<UINT64>(MB))
        oss << (bytes / MB) << L" MB";
    else if (bytes >= static_cast<UINT64>(KB))
        oss << (bytes / KB) << L" KB";
    else
        oss << bytes << L" B";

    return oss.str();
}

/// Print memory usage
void ResourceManager::PrintMemoryUsage() {
    std::wstring usage = GetMemoryUsageWString();
    OutputDebugStringW(usage.c_str());
}

/// Return memory usage info as string
wstring ResourceManager::GetMemoryUsageWString()
{
    DXGI_QUERY_VIDEO_MEMORY_INFO memInfo = {};
    HANDLE hProcess = GetCurrentProcess();
    PROCESS_MEMORY_COUNTERS_EX pmc;
    pmc.cb = sizeof(PROCESS_MEMORY_COUNTERS_EX);
    HRESULT hr = dxgiAdapter->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &memInfo);

    std::wostringstream oss;
    oss << L"------- �޸� ��ȸ -------\n";

    if (GetProcessMemoryInfo(hProcess, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
        oss << L"VRAM: " << FormatBytes(memInfo.CurrentUsage).c_str() << L"\n";
        oss << L"DRAM: " << FormatBytes(pmc.WorkingSetSize).c_str() << L"\n";
        oss << L"PageFile: " << FormatBytes(pmc.PagefileUsage - pmc.WorkingSetSize).c_str() << L"\n";
    }
    else {
        oss << L"�޸� ���� ��ȸ ����\n";
    }

    oss << L"-----------------------------\n";
    return oss.str();
}

/// Trim unused resources
void ResourceManager::Trim() {
    // �Ⱦ��� ���ҽ� �ʿ��� ���� (ControlBlock �Ҹ�)
    for (auto it = map_texture2D.begin(); it != map_texture2D.end(); )
    {
        if (it->second.expired())
            it = map_texture2D.erase(it);
        else
            ++it;
    }

    // �� ���� ���ҽ� ���� (VRAM/DRAM/pagefile.sys( ���ҽ� ����)
    dxgiDevice->Trim();

    OutputDebugStringA("[Woo Engine] Trim() ���ҽ� ����\n");
}

/// Texture2D Resource Create
shared_ptr<Texture2D> ResourceManager::CreateTexture2D(string filePath)
{
    string key = filePath;
    auto it = map_texture2D.find(key);

    // map�� weak_ptr�� ���� ���
    if (it != map_texture2D.end())
    {
        // 1) �ν��Ͻ��� ����ִٸ� shared_ptr return
        if (!it->second.expired()) return it->second.lock();

        // �ν��Ͻ��� �Ҹ�Ȼ��¶�� weak_ptr�� �����ϰ� �� ���ҽ� ����
        else map_texture2D.erase(it);
    }

    // 2) Create new resource
    // �� ���ڴ� ����
    ComPtr<IWICBitmapDecoder> decoder;
    wstring wpath(filePath.begin(), filePath.end());
    HRESULT hr = wicImagingFactory->CreateDecoderFromFilename(
        wpath.c_str(), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder);
    if (FAILED(hr)) {
        wcout << L"[ERROR] Decoder ���� ����: " << wpath << endl;
        return nullptr;
    }

    // �� ù ��° ������ ���
    ComPtr<IWICBitmapFrameDecode> frame;
    hr = decoder->GetFrame(0, &frame);
    if (FAILED(hr)) {
        wcout << L"[ERROR] Frame �������� ����: " << wpath << endl;
        return nullptr;
    }

    // �� ���� ��ȯ�� ����
    ComPtr<IWICFormatConverter> converter;
    hr = wicImagingFactory->CreateFormatConverter(&converter);
    if (FAILED(hr)) {
        wcout << L"[ERROR] FormatConverter ���� ����: " << wpath << endl;
        return nullptr;
    }

    // �� ���� ��ȯ �ʱ�ȭ (32bppPBGRA)
    hr = converter->Initialize(
        frame.Get(),
        GUID_WICPixelFormat32bppPBGRA,
        WICBitmapDitherTypeNone,
        nullptr,
        0.0f,
        WICBitmapPaletteTypeCustom
    );
    if (FAILED(hr)) {
        wcout << L"[ERROR] Format ��ȯ ����: " << wpath << endl;
        return nullptr;
    }

    // �� Bitmap �Ӽ� ����
    D2D1_BITMAP_PROPERTIES1 bmpProps = D2D1::BitmapProperties1(
        D2D1_BITMAP_OPTIONS_NONE,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)
    );

    // �� Bitmap ����
    shared_ptr<Texture2D> new_texture2D = make_shared<Texture2D>();
    hr = RenderSystem::Get().renderTarget->CreateBitmapFromWicBitmap(
        converter.Get(), &bmpProps, &new_texture2D->texture2D);
    if (FAILED(hr)) {
        wcout << L"[ERROR] Bitmap ���� ����: " << wpath << endl;
        return nullptr;
    }

    // texture data save
    new_texture2D->filePath = filePath;
    new_texture2D->size = new_texture2D->texture2D->GetSize();

    // map�� �����ϰ� shared_ptr return
    map_texture2D[key] = new_texture2D;
    return new_texture2D;
}

/// CreateSprite - Texture2D ��ü ����
shared_ptr<Sprite> ResourceManager::CreateSprite(shared_ptr<Texture2D> texture, string spriteName)
{
    if (!texture) 
    {
        OutputDebugStringA("Texture2D�� nullptr�Դϴ�.\n");
        return nullptr;
    }

    auto it = map_sprite.find(spriteName);
    if (it != map_sprite.end())
    {
        // 1) �ν��Ͻ��� ����ִٸ� shared_ptr return
        if (!it->second.expired()) return it->second.lock();
        else map_sprite.erase(it);
    }

    // 2) Create new resource
    shared_ptr<Sprite> newSprite = make_shared<Sprite>(texture, spriteName);
    map_sprite[spriteName] = newSprite;
    return newSprite;
}

/// CreateSprite - Texture2D �Ϻ� ����
shared_ptr<Sprite> ResourceManager::CreateSprite(shared_ptr<Texture2D> texture, string spriteName, D2D1_RECT_F rect, D2D1_POINT_2F pivotPoint)
{
    if (!texture)
    {
        OutputDebugStringA("Texture2D�� nullptr�Դϴ�.\n");
        return nullptr;
    }

    auto it = map_sprite.find(spriteName);
    if (it != map_sprite.end())
    {
        // 1) �ν��Ͻ��� ����ִٸ� shared_ptr return
        if (!it->second.expired()) return it->second.lock();
        else map_sprite.erase(it);
    }

    // 2) Create new resource
    shared_ptr<Sprite> newSprite = make_shared<Sprite>(texture, spriteName, rect, pivotPoint);
    map_sprite[spriteName] = newSprite;
    return newSprite;
}

/// Create AudioClip
shared_ptr<AudioClip> ResourceManager::CreateAudioClip(string filePath)
{
    string key = filePath;
    auto it = map_AudioClip.find(key);

    // map�� weak_ptr�� ���� ���
    if (it != map_AudioClip.end())
    {
        // 1) �ν��Ͻ��� ����ִٸ� shared_ptr return
        if (!it->second.expired()) return it->second.lock();

        // �ν��Ͻ��� �Ҹ�Ȼ��¶�� weak_ptr�� �����ϰ� �� ���ҽ� ����
        else map_AudioClip.erase(it);
    }

    // 2) Create new resource
    shared_ptr<AudioClip> newAudioClip = make_shared<AudioClip>(filePath);
    map_AudioClip[filePath] = newAudioClip;
    return newAudioClip;
}