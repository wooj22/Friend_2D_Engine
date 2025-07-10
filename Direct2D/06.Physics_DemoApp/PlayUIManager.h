#pragma once
#include "../Direct2D_EngineLib/UI_Button.h"
#include "../Direct2D_EngineLib/UI_Image.h"
#include"../Direct2D_EngineLib/UI_Text.h"
#include "../Direct2D_EngineLib/GameObject.h"

class PlayUIManager : public GameObject
{
public:
    UI_Text* adviceText;
    UI_Button* backButton;

public:
    // game object cycle
    PlayUIManager() {}
    ~PlayUIManager() override {}

    // 오브젝트가 생성될 때
    void Awake() override             
    {

    }

    // Scene의 Start (씬의 모든 오브젝트가 생성되고 난 뒤)
    void SceneStart() override     
    {
        adviceText->rectTransform->SetPosition(0, 350);
        adviceText->rectTransform->SetSize(800, 200);
        adviceText->screenTextRenderer->SetFontSize(25);
        adviceText->screenTextRenderer->SetText(L"[Spacebar]를 누르면 고양이가 생성됩니다.");
        adviceText->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::LightSkyBlue));

        backButton->rectTransform->SetPivot(0, 1);
        backButton->rectTransform->SetPosition(-680, 380);
        backButton->rectTransform->SetSize(50, 50);
        backButton->imageRenderer->SetBaseColor(D2D1::ColorF(D2D1::ColorF::LightSkyBlue));
        backButton->screenTextRenderer->SetText(L"Back");
        backButton->screenTextRenderer->SetFontSize(20);
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

