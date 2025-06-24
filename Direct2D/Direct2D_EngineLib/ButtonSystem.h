#pragma once
#include <vector>
#include "Singleton.h"
using namespace std;

class Button;
class ButtonSystem : public Singleton<ButtonSystem>
{
private:
	vector<Button*> components;

public:
	// componenet
	void Regist(Button* component);
	void Unregist(Button* component);

	// component system
	void Update();
};

