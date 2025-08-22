#pragma once
#include "../Friend_2D_EngineLib/Script.h"
#include "../Friend_2D_EngineLib/GameObject.h"
#include "../Friend_2D_EngineLib/Time.h"
#include "../Friend_2D_EngineLib/SpriteRenderer.h"


class AfterImage : public Script
{
private:
    float lifeTime = 0.5f;
    float timer = 0.0f;
    float initialAlpha = 1.0f;

    SpriteRenderer* renderer = nullptr;

public:
    void Awake() override
    {
        renderer = gameObject->GetComponent<SpriteRenderer>();
        renderer->layer = 23;
    }

    void Update() override
    {
        if (!renderer) return;

        timer += Time::GetDeltaTime();
        float t = timer / lifeTime;
        float currentAlpha = initialAlpha * (1.0f - t); // ���� �����
        renderer->SetAlpha(currentAlpha);

        if (timer >= lifeTime)
        {
            gameObject->Destroy();
        }
    }

    void SetInitialAlpha(float alpha)
    {
        initialAlpha = alpha;
    }
};