#pragma once
#include <vector>
#include "Singleton.h"
using namespace std;

/* ButtonSystem�� ����
* 1. Button Component update 
     -> �ڽ��� ������ Ŭ���Ǿ��ִ��� �����ϰ� �̺�Ʈ �߻��� �ݹ� �Լ� invoke
*/

class Button;
class ButtonSystem : public Singleton<ButtonSystem>
{
private:
	vector<Button*> components;
	vector<Button*> pending_components;

public:
	// componenet
	void Regist(Button* component);
	void Unregist(Button* component);

	// component system
	void Update();
};

