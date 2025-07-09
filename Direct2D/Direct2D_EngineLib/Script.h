#pragma once
#include "Component.h"
#include "ScriptSystem.h"
#include "GameObject.h"

/* [Script Conponent]
* GameObject의 여러 Component들을 controll하는 script 컴포넌트이다.
* 게임 콘텐츠에서는 이 class를 상속받은 script를 작성하여
* 기능별로 스크립트를 분리하고, 재활용 할 수 있다. ex) Movement.cs, Inventory.cs
* 
* Awake(), Start() -> SceneManager에서 씬의 Awake(), Start() 이후에 호출
*                     started 플래그 체크를 하기 때문에 udpate중에도 호출 보장  
* Update(), FixedUpdate() ->메인 루프에서 호출한다.
*/

class Script : public Component
{
public:
    bool started = false; // update중 생성되는 경우를 위한 flag

    /* script component cycle */
	Script() { ScriptSystem::Get().Regist(this); }
	~Script() override { ScriptSystem::Get().Unregist(this); }

	void OnEnable() override {}        // 컴포넌트 활성화시
    virtual void Awake() {}            // 오브젝트의 모든 컴포넌트가 생성된 직후 시점 1회 호출
    virtual void Start() {}            // Awake() 이후 시점 1회 호출
    virtual void Update() {}           // 프레임 단위 반복 호출
    virtual void FixedUpdate() {}      // 물리 업데이트 0.02f 보장 반복 호출
	void OnDestroy() override {}       // 컴포넌트 or 오브젝트 소멸 시점

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



