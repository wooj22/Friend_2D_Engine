#include "BitmapRenderer.h"

void BitmapRenderer::AxisCoreection() {
	if (!image) return;

	D2D1_SIZE_F size = image->GetSize();
	destRect = {
		-size.width / 2.0f,  // 왼쪽
		-size.height / 2.0f, // 위
		size.width / 2.0f,   // 오른쪽
		size.height / 2.0f   // 아래
	};
}

void BitmapRenderer::Render() 
{
	// 추가로 축 보정이 필요함. 지금은 이미지의 좌측 위가 중점인데,
	// 그 좌표에 이미지가 중점으로 출력되도록 옮겨서 그려야함
	// 이미지 멤버는 Microsoft::WRL::ComPtr<ID2D1Bitmap1> image; 로 선언되어있음
	D2DRenderManager::Get().renderTarget->SetTransform(transform.GetScreenMatrix());
	D2DRenderManager::Get().renderTarget->DrawBitmap(image.Get(), destRect);
}

void BitmapRenderer::UnInit()
{
	image = nullptr;
}