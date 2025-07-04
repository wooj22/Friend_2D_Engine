#pragma once
#include "../Direct2D_EngineLib/AnimationClip.h"

class CatIdleClip : public AnimationClip
{
public:
	CatIdleClip() 
	{
		auto idleImage = ResourceManager::Get().CreateTexture2D("../Resource/Texture/Cat_Idle.png");
		LoadSpritesFromJson(idleImage, "../Resource/Data/SpriteSheet/Cat_Idle_Sprites.json");
		LoadAnimationClipFromJson(idleImage, "../Resource/Data/AnimationClip/Cat_Idle_AniClip.json");
	}
	~CatIdleClip() override {}

};

