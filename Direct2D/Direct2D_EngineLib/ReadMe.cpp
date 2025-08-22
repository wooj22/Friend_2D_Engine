
// Read Me!
// ����� ���� ���� �Ұ�
// �ڼ��� ������ �����ص� Ŭ���� [F12] Ÿ�� ���� ���ּ���.


/*---------------------------------------------------------------------------------*/
/*--------------- ���� ������ �ۼ��� �˾ƾ� �� Cycle, Utility -----------------------*/
/*--------------------------------------------------------------------------------*/

class GameObject;
// ���� ������ ������Ʈ������ GameObject�� ��ӹ��� �پ��� GameObject�� �����ϰ�
// �������� �ش� GameObject�� Create�� �մϴ�.
// ��ȿ�� �˻��  ObjectTable::Get().IsValid(object)�� ���� �̷�����ϴ�.
{
	/* [GameObject Cycle] */		   // ! ��� �Ƚᵵ ��. ������ ���ӿ�����Ʈ ���� ��쿡 Script ������Ʈ�� ����� ������ ������ ���� ����Ŭ
	virtual void Awake() {};           // ������Ʈ�� ������ ��, ������ ����
	virtual void SceneStart() {};      // Scene�� Start -> Update�� SceneStart() ȣ�� ���� x
	virtual void Update() {};          // Scene�� Update
	virtual void Destroyed() {};       // Scene�� Exit, GameObject Delete


	/* [Utility] */
	// 1. name, tag
	// �����ڷ� ���� �����ϸ� puplic ��������� �ٷ� ���� ������
	// 
	// 2. Find
	// name, tag�� ���ӿ�����Ʈ�� ã�� �����͸� ���� �� ����		
	// 
	// 3. Destory
	// - player.Destory()�� this ���ӿ�����Ʈ ���� ����
	// - GameObject::Destroy(������)�� ���� ������Ʈ ���� ����
	//
	// 4. SetActive
	// - bool���� ������ ���ӿ�����Ʈ�� Ȱ��ȭ/ ��Ȱ��ȭ �� �� ����
	// - �ڽ� ������Ʈ���� ��� Ȱ��ȭ/��Ȱ��ȭ ��
}


class Component;
// ��� ������Ʈ�� �� Component�� ��ӹ޾� �����������, 
// ��ȿ�� �˻��  ObjectTable::Get().IsValid(object)�� ���� �̷�����ϴ�.
{
	/* [Component Cycle] */
	virtual void OnEnable_Inner() = 0;    // ������Ʈ Ȱ��ȭ��
	virtual void OnDisable_Inner() = 0;   // ������Ʈ ��Ȱ��ȭ��
	virtual void OnDestroy_Inner() = 0;   // ������Ʈ or ���ӿ�����Ʈ �ı���

	// SetEnabled
	// ������Ʈ Ȱ��ȭ/��Ȱ��ȭ ���θ� ���� �� ����
}


class Script;
// Component�� ��ӹ޾� ������� ����� Ŀ���ҿ� ������Ʈ��, ����Ƽ�� �������̾��� �����ϸ� �˴ϴ�.
// ���� ������������ Script�� ��ӹ��� ���� ��ũ��Ʈ ������Ʈ�� ����� ������ ������ �ۼ��ϸ� �˴ϴ�.
// ��ȿ�� �˻��  ObjectTable::Get().IsValid(object)�� ���� �̷�����ϴ�.
{
	/* [script component cycle] */
	virtual void OnEnable() {}          // ������Ʈ Ȱ��ȭ��
	virtual void OnDisable() {}         // ������Ʈ ��Ȱ��ȭ��
	virtual void Awake() {}             // Update() ���� 1ȸ ȣ��
	virtual void Start() {}             // Awake() ���� Update() ���� ���� 1ȸ ȣ��
	virtual void Update() {}            // ������ ���� �ݺ� ȣ��
	virtual void FixedUpdate() {}       // ���� ������Ʈ 0.02f ���� �ݺ� ȣ��
	virtual void LateUpdate() {}		// ī�޶� ��
	virtual void OnDestroy() {}         // ������Ʈ or ������Ʈ �Ҹ� ����

	/* [collision event] */
	// trigger
	virtual void OnTriggerEnter(ICollider* other, const ContactInfo& contact) {}
	virtual void OnTriggerStay(ICollider* other, const ContactInfo& contact) {}
	virtual void OnTriggerExit(ICollider* other, const ContactInfo& contact) {}

	// collision
	virtual void OnCollisionEnter(ICollider* other, const ContactInfo& contact) {}
	virtual void OnCollisionStay(ICollider* other, const ContactInfo& contact) {}
	virtual void OnCollisionExit(ICollider* other, const ContactInfo& contact) {}
}



/*---------------------------------------------------------------*/
/*--------------- Component & Component System  -----------------*/
/*--------------- �ȿ� ���� ���� �о��ּ���  ------------------*/
/*--------------------------------------------------------------*/
class TransformSystem;		// trasnfrom system
class Transform;
class RectTransform;

class RenderSystem;			// render system
class SpriteRenderer;
class ImageRenderer;
class WorldTextRenderer;
class ScreenTextRenderer;

class CameraSystem;			// camera system
class Camera;
	
class ScriptSystem;			// script system
class Script;

class PhysicsSystem;		// physics system
class Rigidbody;

class ColliderSystem;		// collider system
class BoxCollider;
class CircleCollider;

class AnimatorSystem;		// animator system
class Animator;

class UISystem;				// ui system
class Button;
class Slider;

class AudioSystem;			// audio system
class AudoiSource;




/*---------------------------------------------------------------*/
/*---------------------- Static System --------------------------*/
/*--------------------------------------------------------------*/
class Input;
class Time;
class InvokeSystem;



/*---------------------------------------------------------------*/
/*-------------------  ���ҽ� ��Ȱ�� ��� ------------------------*/
/*--------------- �ȿ� ���� ���� �о��ּ���  ------------------*/
/*--------------------------------------------------------------*/
class ResourceManager;



/*------------------------------------------------------------*/
/*------------------ �׷��� ��ü ���� ------------------------*/
/*----------------------------------------------------------*/
class Texture2D;
class Sprite;



/*--------------------------------------------------------------*/
/*---------------- �̸� �����ص� GameObject --------------------*/
/*------------------------------------------------------------*/
class UI_Text;
class UI_Image;
class UI_Button;




/*-------------------------------------------------------------------*/
/*---------------------- Animatio FSM �ý��� ------------------------*/
/*------------------------------------------------------------------*/
/* Animator -> AnimatorController -> AnimationBaseState -> AnimationClip */

class Animator;						// "Component" ����� animator controller update, SpriteRenderer�� sprite�� ���� udpate
class AnimatorController;			// "�Ϲ� Class" ��ϵ� state�� ���� FSM �ý��� ��� -> current sprite update
class AnimationBaseState;			// "�Ϲ� Class" �� animation clip�� ���� state, Enter(), Update(), Eixt()�� transition �ڵ� �ۼ� ����
class AnimationClip;				// "�Ϲ� Class" animation clip asset



/*-------------------------------------------------------------------*/
/*-------------------------    Physics   ---------------------------*/
/*------------------------------------------------------------------*/
class Rigidbody;

// Collision Detection Mode
// 1. Discrete(Defualt) : �����Ӹ��� �ܼ� ��ġ üũ (������ ���� �հ� �� ����)
// 2. Continuous : SweepTest�� �̿��Ͽ� ���� �����Ӱ� ���� �������� �̵���λ����� step�� �ݶ��̴��� �и鼭 �浹 �˻�


/*-------------------------------------------------------------------*/
/*-------------------------   Collision  ---------------------------*/
/*-----------------------------------------------------------------*/
/* ColliderSystem -> ICollider(Box, Circle) -> Script Event Func */

class ColliderSystem;
// �ݶ��̴����� �����Ǹ� ColliderSystem�� ��ϵǰ�,
// ���� udpate �ֱ⸶�� �� �ݶ��̴����� �������ִ� aabb�� ���� �����ϰ�, 
// sap �˰����� Ȱ���Ͽ� ��� �ݶ��̴��� ���� �浹 üũ�� �����Ѵ�.
// ���� �� �ݶ��̴��� �浹�ߴٸ� �ش� �ݶ��̴����� ���� �����ӿ� �浹�� �ݶ��̴� map �����̳ʿ� �浹 ������ �߰��Ѵ�.

class ICollider;
class BoxCollider;
class CircleCollider;
// ColliderSystem���� �浹 üũ�϶�� ��� �ݶ��̴��� �����ָ�, �ش� �ݶ��̴��� Type�� �Ǻ��Ͽ� �˸´� �浹 üũ�� �����Ѵ�.
// �̶� �浹�� ��� ContactInfo(�浹 ����, �浹 ��������, ����)�� �Բ� ����Ѵ�.
// �浹�� �ݶ��̴��� �����ϱ� ���� unordered_map<ICollider*, ContactInfo>�� ���� ������ map, ���� ������ map���� �����ϸ�
// �̹� �������� �浹 ����� ��� ������ �̸� ���Ͽ� Enter, Stay, Exit�� ȣ���Ѵ�.
// => �̶� �� �ݶ��̴��� ��ϵǾ��ִ� ���ӿ�����Ʈ�� Script ������Ʈ�� �̺�Ʈ�Լ����� ȣ�����ش�.

// OnCollision�ÿ��� rigidbody�� ���� ��쿡�� Script�� Collision �̺�Ʈ�� �����ϸ�
// rigidbody�� contact ������ �Ѱ� �浹�Ѹ�ŭ transform�� �����ϰ� �Ѵ�. (kinematic�� �ƴ� ��쿡��)
// �� normal > 0�� ����� Enter�� Exit�� üũ�Ͽ� rigidbody�� isgrounded �÷��׸� �����Ͽ� 
// rigidbody ���ο��� �߷��� �ʱ�ȭ�� �� �ֵ��� �Ѵ�.

class Script;
// Script ������Ʈ�� �ִ� �浹 �̺�Ʈ �Լ��� �� ���ϰ� �������̵��ؼ� ���� �ȴ�! 
// ������ �˾Ƽ� ȣ�����ش�.


// [Collision vs Trigger]
// - Collistion �̺�Ʈ�� ������ Rigidbody�� �־�߸� Script�� ���޵˴ϴ�.
// - Collistion �̺�Ʈ �߻��� Rigidbody�� �־�߸� �浹 ������ �˴ϴ�. (kinematic�� �ƴ� ��쿡)

// - �浹�� �� �ݶ��̴��� �ϳ��� isTrigger��� ���� ��ο� Trigger �̺�Ʈ�� ���޵˴ϴ�. (�浹 ���� x)
// - Tirgger �̺�Ʈ�� Rigidbody�� ���� ���� ������ Script�� ���޵˴ϴ�.

// 1. collision vs collision 
//	  => Rigidbody�� �پ��ִ� ��쿡 CollisionEvent ȣ��, �浹 ����

// 2. collision vs trigger 
//	  => TriggerEnvet ȣ��, �浹 ���� x

// 3. trigger vs trigger 
//	  => TriggerEnvet ȣ��, �浹 ���� x


// Q. ���� kinematic�̶��?

// 1. Rigidbody + collision     vs     Rigidbody + collision
//  -> Collision�̺�Ʈ + �浹������      -> Collision�̺�Ʈ + �浹����x

// 2. Rigidbody(kinematic) + collision   vs    Rigidbody + collision
// -> Collision�̺�Ʈ + �浹����x               -> Collision�̺�Ʈ + �浹������ 

// 3. Rigidbody(kinematic) + collision   vs    Rigidbody(kinematic) + collision
// -> Collision�̺�Ʈ + �浹����x               -> Collision�̺�Ʈ + �浹����x 

// �� kinematic�� ��쿡�� collision �̺�Ʈ�� ȣ�� ������, �浹 ������ ���� �ʴ´�.



/*------------------------------------------------------------------*/
/*-------------------------   Ray Cast  ---------------------------*/
/*-----------------------------------------------------------------*/
struct Ray;
struct RaycastHit;
class ColliderSystem;

// ���� ���������� Ray�� �����ϰ�(Ray::origin, Ray::direction)
// ColliderSystem::Raycast() �Լ��� ȣ���Ͽ� Ray�� ������,
// �浹 ������ ��� RaycastHit ����ü�� ��ȯ�մϴ�. (���� ����� �ݶ��̴� 1��)
// Raycast�� isTrigger false�� �ݶ��̴��� ���ؼ��� �浹 üũ�� �����մϴ�.





/*-------------------------------------------------------------------*/
/*-------------------------   Render    ----------------------------*/
/*-----------------------------------------------------------------*/
class RenderSystem;
class IRenderer;
class SpriteRenderer;
class ImageRenderer;			// ImageRenderer�� �߰��� Filltype ������ �����ϴ�

// RenderType�� ���� GameObject�� ���� �׸��� UI�� �׸���.
// RenderMode�� ���� �ٸ� ���� ü���� �����ϸ� �⺻�� Unlit�̴�.
// �̶� Text ���� ���������� RenderMode�� ������ ���� ������,
// ������ bitmap Image�� ������ �ȴ�. (SpriteRenderer, ImageRenderer�� sprite �����)


// SpriteRenderer�� ImageRenderer���� sprite�� ����Ʈ ȿ���� �ް�ʹٸ�
// �Ʒ��� ������带 �������־���Ѵ�!

// 1. Unlit	(Default)
//    - Draw Bitmap
//    - �Ϲ� Bitmap �̹����� �׸���.
//    - ���� ������ �Ұ����ϸ� Alpha���� ���� �����ϴ�.

// 2. UnlitColorTint
//    - Draw Image (Crop + ColorEffect)
//    - bitmap �̹����� ColorMatirx�� ������� ���� ��ȯ�� �� �� �׸���.
//    - R, G, B, A ������ �����ϴ�. + ä�� ���� �߰�!

// 3. Lit_Glow
//    - Draw Image (Crop + BlurEffect)
//    - bitmap �̹����� Blurȿ���� �� �̹����� �׸���, �̹����� �׷� �ı� ȿ���� �ش�.
//    - ColorMatrix�� ���� ����� ���̱� ���� ����Ŷ� RGBA, ä�� ��� �������� �ʴ´�.
//      DrawIamge���� A�� ����Ϸ��� ������ colormatrix ���� �ؾ���

// 4. Lit_ColorTint			
//    - Draw Image (Crop + ColorEffect + BlurEffect)
//    - bitmap �̹����� Blurȿ���� �� �̹����� �׸���, �̹����� �׷� �ı� ȿ���� �ش�.
//    - ColorMatrix�� ���� bitmap�� ������ �����ϸ� �׿� ���� ������ �����ȴ�.
//    - R, G, B, A ������ �����ϴ�. + ä�� ���� �߰�!


/*-------------------------------------------------------------------*/
/*--------------------------   Sound    ----------------------------*/
/*-----------------------------------------------------------------*/
// Sound�� FMOD���̺귯���� Ȱ���� �����Ͽ����ϴ�. 
// �������̺귯�� ������ Extern ������ FMOD inc������ lib�� ��� �־�� ����˴ϴ�.
class AudioSystem;		// componet system
class AudioSource;		// component
class AudioClip;		// asset

// AudioSystem���� FMOD �ý����� �����ϰ� ��ü ������� �� ����ǵ��� �ý����� �� ������ update���ݴϴ�.
// AudioSystem�� �⺻������ masterä��, bgmä��, sfxä���� �����Ǿ��ֽ��ϴ�.
// AudioSource�� ���� �ϳ��� ��� ä���� ������, �ϳ��� ä�ο��� �ΰ��� sound�� ���ÿ� ����� �� �����ϴ�.
// AudioSystem�� bgmä��, sfxä�ο� �� AudioSourceä���� ����Ͽ� ��ü ������ �ͽ��� �� �ֽ��ϴ�.
// AudioCilp�� ���� ���� ���ҽ��� ���ҽ� �Ŵ����� ���� �����ؾ��մϴ�. 
// ������ AudioClip�� AudioSource�� set�Ͽ� ���带 �÷����ϸ� �˴ϴ�!