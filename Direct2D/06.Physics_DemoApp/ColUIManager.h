#include "../Direct2D_EngineLib/UI_Button.h"
#include "../Direct2D_EngineLib/UI_Image.h"
#include "../Direct2D_EngineLib/UI_Text.h"
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Input.h"

class ColUIManager : public GameObject
{
public:
    UI_Text* titleText;
    UI_Text* infoText1;
    UI_Text* infoText2;
    UI_Button* backButton;

public:
    ColUIManager() {}
    ~ColUIManager() override {}

    void SceneStart() override
    {
        titleText->rectTransform->SetPosition(0, 350);
        titleText->rectTransform->SetSize(800, 200);
        titleText->screenTextRenderer->SetFontSize(20);
        titleText->screenTextRenderer->SetText(L"Collistion Test Scene!\n콜라이더를 움직여 충돌 이벤트를 확인하세요\n[Spacebar] 로 Collision/ Trigger 전환");
        titleText->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::LightPink));

        infoText1->rectTransform->SetPosition(-100, 200);
        infoText1->rectTransform->SetSize(200, 100);
        infoText1->screenTextRenderer->SetFontSize(16);
        infoText1->screenTextRenderer->SetHorizontalAlign(TextHorizontalAlign::Left);
        infoText1->screenTextRenderer->SetText(L"BoxObject 이동 : wasd");
        infoText1->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::FloralWhite));

        infoText2->rectTransform->SetPosition(100, -200);
        infoText2->rectTransform->SetSize(200, 100);
        infoText2->screenTextRenderer->SetFontSize(16);
        infoText2->screenTextRenderer->SetHorizontalAlign(TextHorizontalAlign::Right);
        infoText2->screenTextRenderer->SetText(L"CircleObject 이동 : 방향키");
        infoText2->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::FloralWhite));

        backButton->rectTransform->SetPivot(0, 1);
        backButton->rectTransform->SetPosition(-680, 380);
        backButton->rectTransform->SetSize(100, 50);
        backButton->imageRenderer->SetBaseColor(D2D1::ColorF(D2D1::ColorF::LightPink));
        backButton->screenTextRenderer->SetText(L"Back");
        backButton->screenTextRenderer->SetFontSize(20);
    }
};