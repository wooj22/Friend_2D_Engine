#pragma once
#include "../Direct2D_EngineLib/Scene.h"
#include "../Direct2D_EngineLib/Input.h"
#include "../Direct2D_EngineLib/Camera.h"
#include "DemoApp.h"

class Scene2 : public Scene
{
private:
	// scene1 objects
	Camera* camera;

public:
	Scene2() = default;
	~Scene2() = default;

	void Awake() override;
	void Start() override;
	void Update() override;
	void Exit() override;
};

