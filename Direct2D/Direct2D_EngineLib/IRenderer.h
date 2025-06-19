#pragma once
#include "Component.h"
// Q. 굳이 IRenderer를 나누는 이유
// A. 확장성 - 현재는 상속관계가 BitmapRenderer밖에 없지만 향후 추가될 가능성이 높음
//          - ShapeRenderer, TextRenderer, SpriteRenderer, EffectRenderer, ParticleRenderer 등
//    의존성 - Render(), UnInit()을 호출하는 RenderManager에서 
//            이 함수 외의 BitmapRenderer멤버에 접근할 일이 없기 때문에 추상 인터페이스를 활용하여 결합도를 낮춤

/* 인터페이스 */
class IRenderer : public Component
{
public : 
	virtual ~IRenderer() = default;

	//void OnEnable() override {};
	virtual void Update() = 0;
	virtual void Render() = 0;
	//void OnDestroy() override {};
};

