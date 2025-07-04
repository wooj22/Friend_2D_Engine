#pragma once
#include "../Direct2D_EngineLib/Scene.h"
#include "../Direct2D_EngineLib/Input.h"
#include "../Direct2D_EngineLib/Camera.h"
#include"../Direct2D_EngineLib/UI_Image.h"
#include"../Direct2D_EngineLib/UI_Text.h"
#include "DemoApp.h"
#include "Cat.h"

/* Animation FSM Test Scene1 */
class Scene1 : public Scene
{
private:
	Camera* camera;
	Cat* cat;

public:
	Scene1() = default;
	~Scene1() = default;

	void Awake() override;
	void Start() override;
	void Update() override;
	void Exit() override;
};
