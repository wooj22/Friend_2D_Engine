#pragma once
#include "../Direct2D_EngineLib/Scene.h"
#include "../Direct2D_EngineLib/Input.h"
#include "../Direct2D_EngineLib/Time.h"

#include "../Direct2D_EngineLib/Camera.h"
#include "DemoApp.h"

#include "PlayUIManager.h"
#include "MapManager.h"
#include "Cat.h"
#include "CatText.h"

class PlayScene : public Scene
{
private:
	// test play¿ë
	bool isCatCreate;

private:
	//Camera_Old* camera;
	GameObject* cam;
	UI_Text* adviceText;

	PlayUIManager* uiManager;
	MapManager* mapManager;
	Cat* player;
	CatText* catText;

public:
	PlayScene() = default;
	~PlayScene() = default;

	void Awake() override;
	void Start() override;
	void Update() override;
	void Exit() override;

private:
	void ChagneBackScene();
	void ChagneNectScene();
};

