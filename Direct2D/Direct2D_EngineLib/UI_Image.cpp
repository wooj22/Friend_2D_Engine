#include "UI_Image.h"

void UI_Image::Awake()
{
	rectTransform = AddComponent<RectTransform>();
	imageRenderer = AddComponent <ImageRenderer>();
}