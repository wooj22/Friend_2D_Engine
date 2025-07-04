#pragma once
#include "../Direct2D_EngineLib/Scene.h"
#include "../Direct2D_EngineLib/Input.h"
#include "../Direct2D_EngineLib/Camera.h"
#include"../Direct2D_EngineLib/UI_Image.h"
#include"../Direct2D_EngineLib/UI_Text.h"
#include "DemoApp.h"

/* Animation FSM Test Scene1 */
class Scene2 : public Scene
{
private:
	Camera* camera;

public:
	Scene2() = default;
	~Scene2() = default;

	void Awake() override;
	void Start() override;
	void Update() override;
	void Exit() override;
};
