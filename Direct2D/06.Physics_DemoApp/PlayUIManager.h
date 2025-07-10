#pragma once
#include "../Direct2D_EngineLib/UI_Button.h"
#include "../Direct2D_EngineLib/UI_Image.h"
#include "../Direct2D_EngineLib/UI_Text.h"
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Input.h"

class PlayUIManager : public GameObject
{
public:
    UI_Text* titleText;
    UI_Text* adviceText;
    UI_Text* memoryInfoText;
    UI_Text* buttonInfoText;
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
        titleText->rectTransform->SetPosition(0, 350);
        titleText->rectTransform->SetSize(800, 200);
        titleText->screenTextRenderer->SetFontSize(25);
        titleText->screenTextRenderer->SetText(L"[Spacebar]를 누르면 고양이가 생성됩니다.");
        titleText->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::LightSkyBlue));

        adviceText->rectTransform->SetPivot(0, 0.5);
        adviceText->rectTransform->SetPosition(-690, -350);
        adviceText->rectTransform->SetSize(400, 200);
        adviceText->screenTextRenderer->SetFontSize(16);
        adviceText->screenTextRenderer->SetHorizontalAlign(TextHorizontalAlign::Left);
        adviceText->screenTextRenderer->SetText(L"플레이어 이동 : [W][A][S][D] + [Shfit]\n카메라 이동 : [<-] [->]\n현재 메모리 확인 [M]");
        adviceText->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::FloralWhite));

        memoryInfoText->rectTransform->SetPivot(1, 0.5);
        memoryInfoText->rectTransform->SetPosition(690, -360);
        memoryInfoText->rectTransform->SetSize(400, 200);
        memoryInfoText->screenTextRenderer->SetFontSize(16);
        memoryInfoText->screenTextRenderer->SetHorizontalAlign(TextHorizontalAlign::Right);
        memoryInfoText->screenTextRenderer->SetText(L"*** memory ***");
        memoryInfoText->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::FloralWhite));

        buttonInfoText-> rectTransform->SetPivot(0, 1);
        buttonInfoText->rectTransform->SetPosition(-615, 380);
        buttonInfoText->rectTransform->SetSize(120, 50);
        buttonInfoText->screenTextRenderer->SetFontSize(16);
        buttonInfoText->screenTextRenderer->SetText(L"<- button click!");
        buttonInfoText->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::FloralWhite));

        backButton->rectTransform->SetPivot(0, 1);
        backButton->rectTransform->SetPosition(-680, 380);
        backButton->rectTransform->SetSize(55, 50);
        backButton->imageRenderer->SetBaseColor(D2D1::ColorF(D2D1::ColorF::LightSkyBlue));
        backButton->screenTextRenderer->SetText(L"Back");
        backButton->screenTextRenderer->SetFontSize(20);
    }

    // Scene의 Update
    void Update()  override           
    {
        if (Input::GetKeyDown('M'))
        {
            memoryInfoText->screenTextRenderer->SetText(ResourceManager::Get().GetMemoryUsageWString());
        }
    }

    // Scene의 Exit, GameObject Delete
    void Destroyed() override         
    {

    }
};

