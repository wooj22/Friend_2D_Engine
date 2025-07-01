#include "ResourceManager.h"
#include "RenderSystem.h"
#include "Texture2D.h"

/// ResourceManager Init
HRESULT ResourceManager::Init()
{
    HRESULT hr;

    // WIC Imaging Factory 생성
    hr = CoCreateInstance(
        CLSID_WICImagingFactory,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(wicImagingFactory.GetAddressOf())
    );
    if (FAILED(hr))
        return hr;

    // RenderSystem에서 D3D11Device 가져오기
    ComPtr<ID3D11Device> d3dDevice = RenderSystem::Get().d3dDevice;
    if (!d3dDevice)
        return E_FAIL;

    // IDXGIDevice 인터페이스 얻기
    ComPtr<IDXGIDevice> dxgiDeviceBase;
    hr = d3dDevice->QueryInterface(dxgiDeviceBase.GetAddressOf());
    if (FAILED(hr))
        return hr;

    // IDXGIDeviceBase -> IDXGIDevice3 변환
    hr = dxgiDeviceBase.As(&dxgiDevice);
    if (FAILED(hr))
        return hr;

    // IDXGIAdapter 얻기
    ComPtr<IDXGIAdapter> dxgiAdapterBase;
    hr = dxgiDevice->GetAdapter(dxgiAdapterBase.GetAddressOf());
    if (FAILED(hr))
        return hr;

    // IDXGIAdapter -> IDXGIAdapter3 변환
    hr = dxgiAdapterBase.As(&dxgiAdapter);
    if (FAILED(hr))
        return hr;

    return S_OK;
}

/// Format bytes to human-readable string
string ResourceManager::FormatBytes(UINT64 bytes) {
    constexpr double KB = 1024.0;
    constexpr double MB = KB * 1024.0;
    constexpr double GB = MB * 1024.0;

    ostringstream oss;
    oss << fixed << setprecision(2);

    if (bytes >= static_cast<UINT64>(GB))
        oss << (bytes / GB) << " GB";
    else if (bytes >= static_cast<UINT64>(MB))
        oss << (bytes / MB) << " MB";
    else if (bytes >= static_cast<UINT64>(KB))
        oss << (bytes / KB) << " KB";
    else
        oss << bytes << " B";

    return oss.str();
}

/// Print memory usage
void ResourceManager::PrintMemoryUsage() {
    DXGI_QUERY_VIDEO_MEMORY_INFO memInfo = {};
    HANDLE hProcess = GetCurrentProcess();
    PROCESS_MEMORY_COUNTERS_EX pmc;
    pmc.cb = sizeof(PROCESS_MEMORY_COUNTERS_EX);
    HRESULT hr = dxgiAdapter->QueryVideoMemoryInfo(0, DXGI_MEMORY_SEGMENT_GROUP_LOCAL, &memInfo);
    if (GetProcessMemoryInfo(hProcess, (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
        string vramStr = "VRAM: " + FormatBytes(memInfo.CurrentUsage) + "\n";
        string dramStr = "DRAM: " + FormatBytes(pmc.WorkingSetSize) + "\n";
        string pageFileStr = "PageFile: " + FormatBytes(pmc.PagefileUsage - pmc.WorkingSetSize) + "\n";

		OutputDebugStringA("---------메모리 조회---------\n");
        OutputDebugStringA(vramStr.c_str());
        OutputDebugStringA(dramStr.c_str());
        OutputDebugStringA(pageFileStr.c_str());
        OutputDebugStringA("-----------------------------\n");
    }
    else {
        OutputDebugStringA("메모리 정보 조회 실패\n");
    }
}

/// Trim unused resources
void ResourceManager::Trim() {
    dxgiDevice->Trim();
}

/// Texture2D Resource Create
shared_ptr<Texture2D> ResourceManager::CreateTexture2D(string filePath) 
{
    string key = filePath;
    auto it = map_texture2D.find(key);

    // map에 weak_ptr이 있을 경우
    if (it != map_texture2D.end())
    {
        // 1) 인스턴스가 살아있다면 shared_ptr return
        if (!it->second.expired()) return it->second.lock();

        // 인스턴스가 소멸된상태라면 weak_ptr을 제거하고 새 리소스 생성
        else map_texture2D.erase(it);
    }

    // 2) Create new resource
    shared_ptr<Texture2D> new_texture2D = make_shared<Texture2D>();
    wstring wpath(filePath.begin(), filePath.end());

    // ① 디코더 생성
    ComPtr<IWICBitmapDecoder> decoder;
    HRESULT hr = wicImagingFactory->CreateDecoderFromFilename(
        wpath.c_str(), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder);
    if (FAILED(hr)) {
        wcout << L"[ERROR] Decoder 생성 실패: " << wpath << endl;
        return nullptr;
    }

    // ② 첫 번째 프레임 얻기
    ComPtr<IWICBitmapFrameDecode> frame;
    hr = decoder->GetFrame(0, &frame);
    if (FAILED(hr)) {
        wcout << L"[ERROR] Frame 가져오기 실패: " << wpath << endl;
        return nullptr;
    }

    // ③ 포맷 변환기 생성
    ComPtr<IWICFormatConverter> converter;
    hr = wicImagingFactory->CreateFormatConverter(&converter);
    if (FAILED(hr)) {
        wcout << L"[ERROR] FormatConverter 생성 실패: " << wpath << endl;
        return nullptr;
    }

    // ④ 포맷 변환 초기화 (32bppPBGRA)
    hr = converter->Initialize(
        frame.Get(),
        GUID_WICPixelFormat32bppPBGRA,
        WICBitmapDitherTypeNone,
        nullptr,
        0.0f,
        WICBitmapPaletteTypeCustom
    );
    if (FAILED(hr)) {
        wcout << L"[ERROR] Format 변환 실패: " << wpath << endl;
        return nullptr;
    }

    // ⑤ Bitmap 속성 설정
    D2D1_BITMAP_PROPERTIES1 bmpProps = D2D1::BitmapProperties1(
        D2D1_BITMAP_OPTIONS_NONE,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)
    );

    // ⑥ Bitmap 생성
    hr = RenderSystem::Get().renderTarget->CreateBitmapFromWicBitmap(
        converter.Get(), &bmpProps, &new_texture2D->texture2D);
    if (FAILED(hr)) {
        wcout << L"[ERROR] Bitmap 생성 실패: " << wpath << endl;
        return nullptr;
    }

    // map에 저장하고 shared_ptr return
    map_texture2D[key] = new_texture2D;
    return new_texture2D;
}