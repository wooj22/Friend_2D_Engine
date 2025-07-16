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
    UI_Text* buttonInfo2Text;
    UI_Button* backButton;
    UI_Button* nextButton;

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
        adviceText->screenTextRenderer->SetText(L"플레이어 이동 : [W][A][S][D], [Shfit], [Spacebar]\n카메라 이동 : [<-] [->]\n현재 메모리 확인 [M]");
        adviceText->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::FloralWhite));

        memoryInfoText->rectTransform->SetPivot(1, 0.5);
        memoryInfoText->rectTransform->SetPosition(690, -360);
        memoryInfoText->rectTransform->SetSize(400, 200);
        memoryInfoText->screenTextRenderer->SetFontSize(16);
        memoryInfoText->screenTextRenderer->SetHorizontalAlign(TextHorizontalAlign::Right);
        memoryInfoText->screenTextRenderer->SetText(L"*** memory ***");
        memoryInfoText->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::FloralWhite));

        buttonInfoText-> rectTransform->SetPivot(0, 1);
        buttonInfoText->rectTransform->SetPosition(-580, 380);
        buttonInfoText->rectTransform->SetSize(120, 50);
        buttonInfoText->screenTextRenderer->SetFontSize(16);
        buttonInfoText->screenTextRenderer->SetText(L"<- button click!");
        buttonInfoText->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::FloralWhite));

        buttonInfo2Text->rectTransform->SetPivot(1, 1);
        buttonInfo2Text->rectTransform->SetPosition(580, 380);
        buttonInfo2Text->rectTransform->SetSize(170, 50);
        buttonInfo2Text->screenTextRenderer->SetFontSize(16);
        buttonInfo2Text->screenTextRenderer->SetHorizontalAlign(TextHorizontalAlign::Right);
        buttonInfo2Text->screenTextRenderer->SetText(L"⭐ 콜리션 테스트 씬->");
        buttonInfo2Text->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::LightBlue));

        auto image = ResourceManager::Get().CreateTexture2D("../Resource/UI_Button2.png");
        auto new_sprite = ResourceManager::Get().CreateSprite(image, "UI_Button2");

        backButton->rectTransform->SetPivot(0, 1);
        backButton->rectTransform->SetPosition(-680, 380);
        backButton->rectTransform->SetSize(100, 50);
        backButton->imageRenderer->sprite = new_sprite;
        backButton->screenTextRenderer->SetText(L"Back");
        backButton->screenTextRenderer->SetFontSize(20);

        nextButton->rectTransform->SetPivot(1, 1);
        nextButton->rectTransform->SetPosition(680, 380);
        nextButton->rectTransform->SetSize(100, 50);
        nextButton->imageRenderer->sprite = new_sprite;
        nextButton->screenTextRenderer->SetText(L"Next");
        nextButton->screenTextRenderer->SetFontSize(20);
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

