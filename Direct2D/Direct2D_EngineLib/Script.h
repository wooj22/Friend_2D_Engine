#pragma once
#include "Component.h"
#include "ScriptSystem.h"

/* [Button Conponent]
* GameObject의 여러 Component들을 controll하는 script 컴포넌트이다.
* 게임 콘텐츠에서는 이 class를 상속받은 script를 작성하여
* 기능별로 스크립트를 분리하고, 재활용 할 수 있다. ex) Movement.cs, Inventory.cs
*/

class Script : public Component
{
public:
	// component cycle
	Script() { ScriptSystem::Get().Regist(this); }
	~Script() override { ScriptSystem::Get().Unregist(this); }

	void OnEnable() override {};
	virtual void Update() = 0;
	void OnDestroy() override {};
};



