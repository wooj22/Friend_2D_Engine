#pragma once
#include "../Direct2D_EngineLib/UI_Button.h"
#include "../Direct2D_EngineLib/UI_Image.h"
#include"../Direct2D_EngineLib/UI_Text.h"
#include "../Direct2D_EngineLib/GameObject.h"

class StartUIManager : public GameObject
{
public:
    UI_Image* backgroundImage;
    UI_Text* titleText;
    UI_Button* startButton;

public:
    // game object cycle
    StartUIManager() {}
    ~StartUIManager() override {}

	// 오브젝트가 생성될 때
	void Awake() override              
	{

	}

	// Scene의 Start (씬의 모든 오브젝트가 생성되고 난 뒤)
    void SceneStartInit() override       
    {
		// background
		backgroundImage->rectTransform->SetPivot(0, 1);
		backgroundImage->rectTransform->SetPosition(-700, 400);
		backgroundImage->rectTransform->SetSize(1400, 800);
		auto sky = ResourceManager::Get().CreateTexture2D("../Resource/Sky.png");
		backgroundImage->imageRenderer->sprite = ResourceManager::Get().CreateSprite(sky, "Sky");

		// text
		titleText->rectTransform->SetPosition(0, 80);
		titleText->rectTransform->SetSize(800, 200);
		titleText->screenTextRenderer->SetFontSize(60);
		titleText->screenTextRenderer->SetText(L"Flatformer DemoApp");
		titleText->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::LightPink));

		// button
		startButton->rectTransform->SetPosition(0, -50);
		startButton->rectTransform->SetSize(180, 70);
		startButton->imageRenderer->SetBaseColor(D2D1::ColorF(D2D1::ColorF::LightPink));
		startButton->screenTextRenderer->SetText(L"Start");
		startButton->screenTextRenderer->SetFontSize(30);
    }

	// Scene의 Update
    void Update()  override             
    {

    }

	// Scene의 Exit, GameObject Delete
    void Destroyed() override 
	{
	
	}         
};

