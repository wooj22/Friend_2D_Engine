

1. 재활용이 가능한 컴포넌트들은 어떤것들이 존재 하는가 ?
- Transform, RectTransform                           - World, UI
- SpriteRenderer, ImageRenderer                      - World, UI
- WorldTextRenderer, ScreenTextRenderer              - World, UI
- Button                                             - UI
- Animator
- Script
- Rigidbody, BoxCollider  // TODO :: 구현중



2. Transform의 소유자는 ? 하나의 게임오브젝트에 멀티 Transform을 허용하는가 ? 월드 Matrix계산은 언제 ?
- Transform은 컴포넌트로, 하나의 게임오브젝트의 하나의 Transform을 가지게 됨(제어로직 x)
- 월드 matrix 계산은 TransformSystem에서 transform이 dirty해진 경우 알아서 update해줌



3. 각 종류별 컴포넌트를 다루는 Manager or System의 역할은 ?
- TransformSystem : ITransfrom(Transform, RectTransform) 컴포넌트 인터페이스 update()
- RenderSystem : IRenderer(SpriteRenderer, ImageRenderer, WorldTextRenderer, ScreenTextRenderer) 컴포넌트 인터페이스 update(), render()
지금 렌더매니저가 없어서 그 기능까지 하고있음.
- ButtonSystem : Button 컴포넌트 update() -> 마우스 클릭 영역 체크 -> 이벤트 발생시 콜백
- AnimatorSystem : 등록된 AnimatorController를 update()시키고, 참조중인 SpriteRenderer의 sprite를 바꿔줌
- ScriptSystem : 유니티 모노비헤이어처럼 실행되도록 구현해놨음
- ColliderSystem :   // TODO :: 구현중
- RigidbodySystem :  // TODO :: 구현중

- Input : Input Static System
- Time : Time Static System

- ResourceManager : 리소스 재활용, 생성



4. 역할 구분이 모호한 RenderManager는 어떻게 분리되었나 ?
- 지금 RenderSystem에 통합되어있음
- rigidbody, collider 마저 만들고 분리 예정(추후 기능 추가를 위해)




5. Scene의 역할은 어디까지 인가 ?
- GameObject 컨테이너 역할(생성, 삭제 관리)
- 현재 mainCamera의 역행렬 update중(Transform의 static으로 선언되어있음)




6. 로딩된 리소스 재활용 방식은 ?
 - class ResourceManager;
- Texture2D, Sprite 재활용중
- // TODO :: AnimationClip도 리소스매니저에서 관리해서 재활용할 예정




7. 위임설계(델리게이트)를 적용한 부분과 방식은 ?
- class Button;->button OnClick() 이벤트 구현



8. 게임오브젝트 또는 컴포넌트의 주소 유효성 검증은 어떤 클래스에서 담당하는가 ?
- 교슈님이 주신 ObjecTable 그대로 구현
- // TODO :: 컴포넌트는 스마트 포인터 구조로 수정할 예정



9. 입력은 어떻게 처리하는가 ?
 - class Input;
 - 정적 클래스로 구현해서 전역에서 쉽게 접근할 수 있도록 함


10. 게임오브젝트도 상속을 사용하였나 ?
 - yes
 - 게임 콘텐츠에서는 GameObject를 상속받은 GameObject를 만들어 원하는대로 컴포넌트를 조합하여 사용하게함
 - ex) Cat.h -> 거의 모든 플젝에 들어잇음
 - 엔진에서는 간단한 게임오브젝트(UI_Button, UI_Image, UI_Text) -> 알아서 컴포넌트 생성되고, 매니저 코드 등에서 원하는대로 set만 하면 됨


11. 컨텐츠 구현은 어떤 클래스를 상속하거나 생성하여 작성하여야 하는가 ?
 - GameObject는 GameObject상속받아서 구현
 - Animation은 AnimationClip을 상속받아 각각 clip을 생성하고
	           AnimationBaseState를 상속받아 각각 state를 생성하고
	           AnimatorController를 상속받아 원하는 state를 넣어 fsm 머신을 만들면 됨



VVV 아래에 연결 클래스들 있습니다 VVV



/*---------------------------------------------------------------------------------*/
/*--------------------- 게임 콘텐츠 작성시 알아야 할 Cycle -------------------------*/
/*-------------------------------------------------------------------------------*/

class GameObject;
{
	/* [GameObject Cycle] */		   // ! 얘는 안써도 됨. 간단한 게임오브젝트 같은 경우에 Script 컴포넌트를 만들기 귀찮기 때문에 냅둔 사이클
	virtual void Awake() {};           // 오브젝트가 생성될 때, 생성자 이후
	virtual void SceneStart() {};      // Scene의 Start -> Update중 SceneStart() 호출 보장 x
	virtual void Update() {};          // Scene의 Update
	virtual void Destroyed() {};       // Scene의 Exit, GameObject Delete
}

class Component;
{
	/* [Component Cycle] */
	virtual void OnEnable() = 0;	   // 컴포넌트 활성화시
	virtual void OnDestroy() = 0;	   // 컴포넌트 or 게임오브젝트 파괴시
}

class Script;
{
	/* [script component cycle] */
	void OnEnable() override {}        // 컴포넌트 활성화시
	virtual void Awake() {}            // 오브젝트의 모든 컴포넌트가 생성된 직후 시점 1회 호출
	virtual void Start() {}            // Awake() 이후 시점 1회 호출
	virtual void Update() {}           // 프레임 단위 반복 호출
	virtual void FixedUpdate() {}      // 물리 업데이트 0.02f 보장 반복 호출
	void OnDestroy() override {}       // 컴포넌트 or 오브젝트 소멸 시점

	// trigger
	virtual void OnTriggerEnter() {}
	virtual void OnTriggerStay() {}
	virtual void OnTriggerExit() {}

	// collision
	virtual void OnCollisionEnter() {}
	virtual void OnCollisionStay() {}
	virtual void OnCollisionExit() {}
}




/*---------------------------------------------------------------*/
/*---------------- 재활용 가능한 Component 종류 ------------------*/
/*--------------------------------------------------------------*/
class Transform;
class RectTransform;

class SpriteRenderer;
class ImageRenderer;
class WorldTextRenderer;
class ScreenTextRenderer;

class Button;
class Animator;
class Script;

//class BoxCollider;
//class Rigidbody;





/*---------------------------------------------------------------*/
/*------------------- Static System 종류 ------------------------*/
/*--------------------------------------------------------------*/
class Input;
class Time;





/*------------------------------------------------------------*/
/*------------------ 그래픽 객체 종류 ------------------------*/
/*----------------------------------------------------------*/
class Texture2D;
class Sprite;





/*--------------------------------------------------------------*/
/*---------------- 미리 정의해둔 GameObject --------------------*/
/*------------------------------------------------------------*/
class UI_Text;
class UI_Image;
class UI_Button;





/*-------------------------------------------------------------------*/
/*---------------------- Animatio FSM 시스템 ------------------------*/
/*------------------------------------------------------------------*/
/* Animator -> AnimatorController -> AnimationBaseState -> AnimationClip */

class Animator;						// "Component" 연결된 animator controller update, SpriteRenderer의 sprite를 직접 udpate
class AnimatorController;			// "일반 Class" 등록된 state에 대해 FSM 시스템 담당 -> current sprite update
class AnimationBaseState;			// "일반 Class" 각 animation clip에 대한 state, Enter(), Update(), Eixt()에 transition 코드 작성 가능
class AnimationClip;				// "일반 Class" animation clip asset


