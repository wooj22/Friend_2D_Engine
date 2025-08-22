#include "Platform.h"
#include "../Direct2D_EngineLib/Scene.h"
#include "../Direct2D_EngineLib/Transform.h"
#include "../Direct2D_EngineLib/SpriteRenderer.h"
#include "../Direct2D_EngineLib/ResourceManager.h"
#include "../Direct2D_EngineLib/SceneManager.h"

Platform::Platform()
{
	// [ ground ]
	ground = SceneManager::Get().GetCurrentScene()->CreateObject<GameObject>();
	ground->name = "Ground";
	ground->tag = "EndLine";
	ground->AddComponent<Transform>()->SetPosition(0.0f, -1050.0f);

	ground_col = ground->AddComponent<BoxCollider>();
	ground_col->size = { 2560.0f, 300.0f };
	ground_col->isFlatform = true;

	// �� �ٱ� ��� 
	mapEdge_l = SceneManager::Get().GetCurrentScene()->CreateObject<GameObject>(); // mapborder 
	mapEdge_l->name = "MapBorder";
	mapEdge_l->tag = "MapBorder";
	mapEdge_l->AddComponent<Transform>()->SetPosition(-1280.0f - 150.0f, 0.0f);
	mapEdge_l_col = mapEdge_l->AddComponent<BoxCollider>();
	mapEdge_l_col->size = { 300.0f, 1920.0f };

	mapEdge_r = SceneManager::Get().GetCurrentScene()->CreateObject<GameObject>();
	mapEdge_r->name = "MapBorder";
	mapEdge_r->tag = "MapBorder";
	mapEdge_r->AddComponent<Transform>()->SetPosition(1280.0f + 150.0f, 0.0f);
	mapEdge_r_col = mapEdge_r->AddComponent<BoxCollider>();
	mapEdge_r_col->size = { 300.0f, 1920.0f };


	// [ Platform ] : ���� �ϴ� ���� 

	// 0
	box_object1 = SceneManager::Get().GetCurrentScene()->CreateObject<BoxObject>({ -370.0f, -840.0f });
	cemetery1 = SceneManager::Get().GetCurrentScene()->CreateObject<Cemetery>({ 380.0f, -840.0f });
	// box_object2 = SceneManager::Get().GetCurrentScene()->CreateObject<BoxObject>({ 900.0f, -840.0f });

	// 1
	platform_long1 = SceneManager::Get().GetCurrentScene()->CreateObject<Platform_Long_Grass>({ -630.0f, -700.0f });
	cemetery2 = SceneManager::Get().GetCurrentScene()->CreateObject<Cemetery>({ -800.0f, -630.0f });
	platform_middle1 = SceneManager::Get().GetCurrentScene()->CreateObject<Platform_Middle>({ 640.0f, -700.0f });

	// 2
	platform_short1 = SceneManager::Get().GetCurrentScene()->CreateObject<Platform_Short_Grass>({ 220.0f, -640.0f });
	platform_long2 = SceneManager::Get().GetCurrentScene()->CreateObject<Platform_Long_Grass>({ 1040.0f, -570.0f });
	cemetery3 = SceneManager::Get().GetCurrentScene()->CreateObject<Cemetery>({ 900.0f, -500.0f });
	platform_wall1 = SceneManager::Get().GetCurrentScene()->CreateObject<Platform_Wall_Grass>({ 1300.0f, -280.0f });

	// 3
	platform_middle2 = SceneManager::Get().GetCurrentScene()->CreateObject<Platform_Middle_Grass>({ -1170.0f, -460.0f });
	platform_wall2 = SceneManager::Get().GetCurrentScene()->CreateObject<Platform_Wall>({ -1280.0f, -170.0f });
	platform_middle3 = SceneManager::Get().GetCurrentScene()->CreateObject<Platform_Middle>({ -365.0f, -460.0f });
	// box_object3 = SceneManager::Get().GetCurrentScene()->CreateObject<BoxObject>({ -445.0f, -380.0f });

	// 4
	platform_short2 = SceneManager::Get().GetCurrentScene()->CreateObject<Platform_Short>({ -950.0f, -280.0f });
	// cemetery4 = SceneManager::Get().GetCurrentScene()->CreateObject<Cemetery>({ -980.0f, -220.0f });
	platform_middle4 = SceneManager::Get().GetCurrentScene()->CreateObject<Platform_Middle_Grass>({ 675.0f, -340.0f });
	box_object4 = SceneManager::Get().GetCurrentScene()->CreateObject<BoxObject>({ 575.0f, -265.0f });

	// 5
	platform_middle5 = SceneManager::Get().GetCurrentScene()->CreateObject<Platform_Middle_Grass>({ 50.0f, -220.0f });

	// 6
	platform_long3 = SceneManager::Get().GetCurrentScene()->CreateObject<Platform_Long_Grass>({ -635.0f, -100.0f });
	box_object5 = SceneManager::Get().GetCurrentScene()->CreateObject<BoxObject>({ -670.0f, -25.0f });
	platform_short3 = SceneManager::Get().GetCurrentScene()->CreateObject<Platform_Short>({ 790.0f, -100.0f });

	// 7
	platform_short4 = SceneManager::Get().GetCurrentScene()->CreateObject<Platform_Short>({ 490.0f, 20.0f });
	platform_middle6 = SceneManager::Get().GetCurrentScene()->CreateObject<Platform_Middle_Grass>({ 1100.0f, 120.0f });
	platform_wall3 = SceneManager::Get().GetCurrentScene()->CreateObject<Platform_Wall>({ 1300.0f, 414.0f });

	// 8 
	platform_middle7 = SceneManager::Get().GetCurrentScene()->CreateObject<Platform_Middle>({ -980.0f, 130.0f });
	cemetery5 = SceneManager::Get().GetCurrentScene()->CreateObject<Cemetery>({ -1070.0f, 210.0f });

	// 9
	platform_middle8 = SceneManager::Get().GetCurrentScene()->CreateObject<Platform_Middle>({ 680.0f, 245.0f });

	// 10
	platform_short5 = SceneManager::Get().GetCurrentScene()->CreateObject<Platform_Short>({ -630.0f, 360.0f });

}