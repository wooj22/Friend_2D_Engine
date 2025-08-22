#pragma once
#include <vector>
#include "Singleton.h"
using namespace std;

/* ScriptSystem�� ����
* 1. Script ������Ʈ�� life cycle�Լ��� �����Ѵ�.
*   - �浹 �̺�Ʈ �Լ��� collider�ʿ��� ȣ���
*/

class Script;
class ScriptSystem : public Singleton<ScriptSystem>
{
private:	
	vector<Script*> components;
	vector<Script*> pending_components;

public:
	// componenet
	void Regist(Script* component);
	void Unregist(Script* component);

	// component system
	void Update();
	void LateUpdate();
	void FixedUpdate();
};