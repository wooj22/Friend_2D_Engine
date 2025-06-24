#include "UI_Button.h"

void UI_Button::Awake() 
{
	rectTransform = AddComponent<RectTransform>();
	imageRenderer = AddComponent <ImageRenderer>();
	button = AddComponent<Button>();
}