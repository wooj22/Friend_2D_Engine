#include "UI_Button.h"

void UI_Button::Awake() 
{
	rectTransform = AddComponent<RectTransform>();
	imageRenderer = AddComponent <ImageRenderer>();
	screenTextRenderer = AddComponent<ScreenTextRenderer>();
	button = AddComponent<Button>();
}