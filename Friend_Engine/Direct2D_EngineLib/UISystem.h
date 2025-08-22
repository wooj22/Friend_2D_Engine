#pragma once
#include <vector>
#include "Singleton.h"
using namespace std;

/* UISystem�� ����
* 1. �� UI ������Ʈ���� Update ȣ�� (button, slider ��)
*/

class I_UI;
class UISystem : public Singleton<UISystem>
{
private:
	vector<I_UI*> components;
	vector<I_UI*> pending_components;

public:
	// componenet
	void Regist(I_UI* component);
	void Unregist(I_UI* component);

	// component system
	void Update();
};

