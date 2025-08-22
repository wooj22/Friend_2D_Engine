#pragma once
#include "../Direct2D_EngineLib/GameObject.h"
#include "../Direct2D_EngineLib/Transform.h"
#include "../Direct2D_EngineLib/SpriteRenderer.h"


/* ���� ǥ�� GameObject */
// Boss GameObject �����ڿ��� ������

class BossFace : public GameObject
{
public:
	// components
	Transform* transform;
	SpriteRenderer* spriteRenderer;

	BossFace()
	{
		transform = AddComponent<Transform>();
		spriteRenderer = AddComponent<SpriteRenderer>();

		name = "BossFace";
		spriteRenderer->layer = 11;
	}
};

