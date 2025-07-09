#include "MenuUIManager.h"

void MenuUIManager::Awake() 
{

}

void MenuUIManager::SceneStart()
{
	// BackGround Image setting
	titleImage->imageRenderer->CreateTexture2D("../Resource/Camera.png");
	titleImage->rectTransform->SetPivot(0.5, 0.5);
	titleImage->rectTransform->SetPosition(-270, 400);
	titleImage->rectTransform->SetSize(180, 100);

	// Title Text setting
	titleText->rectTransform->SetPivot(0.5, 0.5);
	titleText->rectTransform->SetPosition(50, 400);
	titleText->rectTransform->SetSize(500, 100);
	titleText->screenTextRenderer->SetText(L"화살표로 카메라 이동");
	titleText->screenTextRenderer->SetFontSize(50);

	// Button setting
	button1->imageRenderer->CreateTexture2D("../Resource/UI_Button.png");
	button1->rectTransform->SetPivot(0, 1);
	button1->rectTransform->SetPosition(-600, 450);
	button1->rectTransform->SetSize(200, 50);
	button1->screenTextRenderer->SetText(L"Button 1");
	button1->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::Red));

	button2->imageRenderer->CreateTexture2D("../Resource/UI_Button.png");
	button2->rectTransform->SetPivot(0, 1);
	button2->rectTransform->SetPosition(-600, 380);
	button2->rectTransform->SetSize(200, 50);
	button2->screenTextRenderer->SetText(L"Button 2");
	button2->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::Yellow));
}

void MenuUIManager::Update()
{

}

void MenuUIManager::Destroyed()
{

}