#pragma once
#include"../Friend_2D_EngineLib/SceneManager.h"
#include"../Friend_2D_EngineLib/Scene.h"
#include "../Friend_2D_EngineLib/GameObject.h"
#include "../Friend_2D_EngineLib/UI_Image.h"
#include "GameManager.h"

class BossHP : public GameObject
{

public:
	UI_Image* hpBarEmpty;
	UI_Image* hpBarFill;

public:
	BossHP() = default;
	~BossHP() = default;

	void Awake() override;           
	void SceneStart() override;
	void Update() override;         
	void Destroyed() override; 
	void RefreshBossHp(float hp);
};

