#include "UI_Text.h"

void UI_Text::Awake()
{
	rectTransform = AddComponent<RectTransform>();
	screenTextRenderer = AddComponent <ScreenTextRenderer>();
}