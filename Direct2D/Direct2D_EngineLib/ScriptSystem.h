#pragma once
#include <vector>
#include "Singleton.h"
using namespace std;

class Script;
class ScriptSystem : public Singleton<ScriptSystem>
{
private:
	vector<Script*> components;

public:
	// componenet
	void Regist(Script* component);
	void Unregist(Script* component);

	// component system
	void Awake();
	void Start();
	void Update();
	void FixedUpdate();
};

