#pragma once
#include "Vector2.h"
class ICollider;

/* Ray : ���� */
struct Ray
{
	Vector2 origin;				// ray ������
	Vector2 direction;			// ray ���� ����
};


/* RayCastHit : ������ �ݶ��̴��� �浹 ���� */
struct RaycastHit
{
	Vector2 point;				// �浹 ����
	float distance;			    // Ray ���������� �浹 �������� �Ÿ�
	ICollider* collider;		// �浹�� �ݶ��̴�
};

