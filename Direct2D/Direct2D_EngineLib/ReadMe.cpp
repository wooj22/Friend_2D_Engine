
/*---------------------------------------------------------------------------------*/
/*--------------------- 게임 콘텐츠 작성시 알아야 할 Cycle -------------------------*/
/*-------------------------------------------------------------------------------*/

class GameObject;
{
	/* [GameObject Cycle] */		   
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


