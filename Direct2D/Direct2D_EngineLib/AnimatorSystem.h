#pragma once
#include <vector>
#include "Singleton.h"
using namespace std;

class Animator;
class AnimatorSystem : public Singleton<AnimatorSystem>
{
private:
	vector<Animator*> components;

public:
	// componenet
	void Regist(Animator* component);
	void Unregist(Animator* component);

	// component system
	void Update();
};


