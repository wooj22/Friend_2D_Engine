#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h"
#include "../Direct2D_EngineLib/SpriteRenderer.h"

class SkyBackground	: public GameObject
{
public:
    Transform* transform;
    SpriteRenderer* spriteRenderer;

public:
    // game object cycle
    SkyBackground() 
    {
        transform = AddComponent<Transform>();
        spriteRenderer = AddComponent<SpriteRenderer>();

        auto darkSky = ResourceManager::Get().CreateTexture2D("../Resource/DarkSky.png");
        spriteRenderer->sprite = ResourceManager::Get().CreateSprite(darkSky, "DarkSky");
        transform->Scaleing(1.3, 1.3);
    }
    ~SkyBackground() override {}
};

