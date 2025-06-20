#pragma once
#include "../Direct2D_EngineLib/Scene.h"
#include "../Direct2D_EngineLib/InputManager.h"
#include "../Direct2D_EngineLib/Camera.h"
#include "DemoApp.h"
#include "Sun.h"
#include "Earth.h"
#include "Moon.h"

class PlayScene : public Scene
{
private:
	// play scene objects
	Camera* camera;
	Sun* sun;
	Earth* earth;
	Moon* moon; 

public:
	PlayScene() = default;
	~PlayScene() = default;

	void Start() override;
	void Update() override;
	void Exit() override;
};

