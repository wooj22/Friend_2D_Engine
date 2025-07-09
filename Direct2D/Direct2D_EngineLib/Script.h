#pragma once
#include "Component.h"
#include "ScriptSystem.h"
#include "GameObject.h"

/* [Script Conponent]
* GameObject의 여러 Component들을 controll하는 script 컴포넌트이다.
* 게임 콘텐츠에서는 이 class를 상속받은 script를 작성하여
* 기능별로 스크립트를 분리하고, 재활용 할 수 있다. ex) Movement.cs, Inventory.cs
* 
* 
*/

class Script : public Component
{
public:
    /* script component cycle */
	Script() { ScriptSystem::Get().Regist(this); }
	~Script() override { ScriptSystem::Get().Unregist(this); }

	void OnEnable() override {}        // 컴포넌트 활성화시
    virtual void Awake() {}            // 
    virtual void Start() {}            // 
    virtual void Update() {}           // 프레임 단위
    virtual void FixedUpdate() {}      // physice update (0.02f 보장)
	void OnDestroy() override {}       // 

    /* Collition Event */
    // trigger
    virtual void OnTriggerEnter() {}
    virtual void OnTriggerStay() {}
    virtual void OnTriggerExit() {}

    // collision
    virtual void OnCollisionEnter() {}
    virtual void OnCollisionStay() {}
    virtual void OnCollisionExit() {}
};



