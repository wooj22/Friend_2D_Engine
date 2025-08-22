#include "FontLoaderUtil.h"
#include "FontCollectionLoader.h"
#include "RenderSystem.h"
#include <iostream> 

std::vector<uint8_t> FontLoaderUtil::LoadFontFileToMemory(const std::wstring& path)
{
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open font file");
    }

    size_t size = static_cast<size_t>(file.tellg());
    std::vector<uint8_t> buffer(size);

    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char*>(buffer.data()), size);

    return buffer;
}

void FontLoaderUtil::LoadFontFromFile(const std::wstring& filepath)
{
    // 1. ttf ������ �޸𸮷� �б�
    std::vector<uint8_t> fontData;
    try
    {
        fontData = LoadFontFileToMemory(filepath);
    }
    catch (const std::exception& e)
    {
        std::wcerr << L"FontLoaderUtil::LoadFontFromFile - " << e.what() << L"\n";
        return;
    }

    // 2. FontCollectionLoader ���� (���ο��� FontFileLoader � ������)
    collectionLoader = Microsoft::WRL::ComPtr<FontCollectionLoader>(new FontCollectionLoader(fontData.data(), fontData.size()));

    // 3. DirectWrite Factory���� Ŀ���� ��Ʈ �÷��� ����
    // RenderSystem::Get().dWriteFactory �� IDWriteFactory* �� ������ ����
    HRESULT hr = RenderSystem::Get().dWriteFactory->CreateCustomFontCollection(
        collectionLoader.Get(),
        nullptr,
        0,
        &customFontCollection);

    if (FAILED(hr))
    {
        std::wcerr << L"Failed to create custom font collection. HRESULT=" << hr << L"\n";
        customFontCollection = nullptr;
        return;
    }

    std::wcout << L"Custom font collection created successfully.\n";
}

void FontLoaderUtil::LoadFontFromMemory(const void* data, size_t size)
{
    // FontCollectionLoader ���� �� ���
    collectionLoader = Microsoft::WRL::ComPtr<FontCollectionLoader>(new FontCollectionLoader(data, size));
    RenderSystem::Get().dWriteFactory->RegisterFontCollectionLoader(collectionLoader.Get());

    // ��Ʈ �÷��� ����
    RenderSystem::Get().dWriteFactory->CreateCustomFontCollection(
        collectionLoader.Get(),
        nullptr,  // collection key (null�̸� loader ���ο��� ó��)
        0,
        &customFontCollection
    );
}
