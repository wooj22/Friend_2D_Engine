#pragma once
#include <vector>
#include "Singleton.h"
using namespace std;

/* AnimatorSystem�� ����
* 1. Animator ������Ʈ udpate -> �� �ִϸ��̼��� ���������� ���ư�
*/

class Animator;
class AnimatorSystem : public Singleton<AnimatorSystem>
{
private:
	vector<Animator*> components;
	vector<Animator*> pending_components;

public:
	// componenet
	void Regist(Animator* component);
	void Unregist(Animator* component);

	// component system
	void Update();
};


