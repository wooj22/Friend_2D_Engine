#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h"
#include "../Direct2D_EngineLib/Time.h"
#include "SkyBackground.h"
#include "Cloud.h"

class MapManager : public GameObject
{
private:
    Transform* transform;
    float mapslidSpeed = 5.0f;
public:
    // background
	SkyBackground* map1;
	SkyBackground* map2;
	SkyBackground* map3;

    // map object
    Cloud* cloud1;
    Cloud* cloud2;
    Cloud* cloud3;
    Cloud* cloud4;
    Cloud* cloud5;

public:
    // game object cycle
    MapManager() 
    {
        transform = AddComponent<Transform>();
    }
    ~MapManager() override {}

    void Awake() override {}              // 오브젝트가 생성될 때

    void SceneStartInit() override       // Scene의 Start
    {
        map1->transform->SetParent(transform);
        map2->transform->SetParent(transform);
        map3->transform->SetParent(transform);

        map1->transform->SetPosition(-100, 0);
        map2->transform->SetPosition(1110, 0);
        map3->transform->SetPosition(2210, 0);

        cloud1->transform->SetPosition(-50, -100);
        cloud2->transform->SetPosition(400, -70);
        cloud3->transform->SetPosition(800, 0);
        cloud4->transform->SetPosition(1200, 50);
        cloud5->transform->SetPosition(1600, 10);
    }
    void Update()  override              // Scene의 Update
    {
        transform->Translate(-mapslidSpeed * Time::GetDeltaTime(), 0);
    }
    void Destroyed() override {}         // Scene의 Exit, GameObject Delete
};

