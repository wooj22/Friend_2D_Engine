#pragma once
#include "../Direct2D_EngineLib/Script.h"

class CatController : public Script
{
public:
	// component cycle
	CatController() {  }
	~CatController() override { Script::~Script(); }  // 소멸자 호출 필수

	void OnEnable() override;
	void Update() override;
	void OnDestroy() override;
};

