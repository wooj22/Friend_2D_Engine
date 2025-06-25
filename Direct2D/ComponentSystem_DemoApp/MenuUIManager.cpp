#include "MenuUIManager.h"

void MenuUIManager::Awake() 
{

}

void MenuUIManager::Start()
{
	// Button ÃÊ±âÈ­
	button1->imageRenderer->SetImage(L"../Resource/UI_Button.png");
	button1->rectTransform->SetPivot(0, 1);
	button1->rectTransform->SetPosition(-600, 450);
	button1->rectTransform->SetSize(200, 50);
	button1->screenTextRenderer->SetText(L"Button 1");
	button1->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::Red));

	button2->imageRenderer->SetImage(L"../Resource/UI_Button.png");
	button2->rectTransform->SetPivot(0, 1);
	button2->rectTransform->SetPosition(-600, 380);
	button2->rectTransform->SetSize(200, 50);
	button2->screenTextRenderer->SetText(L"Button 2");
	button2->screenTextRenderer->SetColor(D2D1::ColorF(D2D1::ColorF::Yellow));
}

void MenuUIManager::Update()
{

}

void MenuUIManager::Destroy()
{

}