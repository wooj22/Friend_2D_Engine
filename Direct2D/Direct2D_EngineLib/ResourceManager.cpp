#include "ResourceManager.h"
#include "RenderSystem.h"
#include "Texture2D.h"


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