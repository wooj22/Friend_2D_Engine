#pragma once
#include "../Direct2D_EngineLib/Scene.h"

class PlayScene : public Scene
{
public:
	PlayScene() = default;
	~PlayScene() = default;

	void Start() override;
	void Update() override;
	void Exit() override;
};

