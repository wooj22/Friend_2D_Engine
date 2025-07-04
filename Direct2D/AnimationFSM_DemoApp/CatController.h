#pragma once
#include "../Direct2D_EngineLib/Script.h"

class CatController : public Script
{
public:
	void OnEnable() override;
	void Update() override;
	void OnDestroy() override;
};

