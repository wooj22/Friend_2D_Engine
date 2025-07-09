#pragma once
#include "../Direct2D_EngineLib/Scene.h"
#include "../Direct2D_EngineLib/Input.h"
#include "../Direct2D_EngineLib/Time.h"
#include "../Direct2D_EngineLib/Camera.h"
#include "DemoApp.h"

#include "PlayUIManager.h"
#include "MapManager.h"
#include "Cat.h"

class PlayScene : public Scene
{
private:
	Camera* camera;
	UI_Text* adviceText;
	UI_Button* backButton;

	PlayUIManager* uiManager;
	MapManager* mapManager;
	Cat* player;

public:
	PlayScene() = default;
	~PlayScene() = default;

	void Awake() override;
	void Start() override;
	void Update() override;
	void Exit() override;

private:
	void ChagneStartScene();
};

