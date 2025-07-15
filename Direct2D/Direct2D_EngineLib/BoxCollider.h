#pragma once
#include "ICollider.h"
#include "ColliderSystem.h"

/* [BoxCollider Component]
* 박스 형태의 충돌 영역을 지정하여 충돌 체크를 담당하는 컴포넌트
* transform의 position을 중점으로 offset만큼 떨어뜨린 size의 콜라이더 영역을 가진다.
* bound 정보를 Update하며 ICollider를 상속받은 모든 종류의 콜라이더와의 상호작용을 지원한다.
* isTrigger 플래그를 설정하여 Block, Overlap 처리를 지정할 수 있다.
* ColliderSystem에 등록되어 충돌 발생시 충돌 이벤트를 호출하게 되고,
* 각 이벤트 종류에 맞게 Script 컴포넌트를 찾아 이벤트 함수를 호출해준다. -> 유니티처럼 사용 가능하도록
* Block(collistion mode)시에는 transform의 이전 프레임 position으로 되돌아가게 한다.
* 
* TODO :: 축별 이동 제한 로직 추가
* 현재는 중력 적용 모드를 고려하여 충돌중에는 yPos만 못움직이게 막아두고 있는데
* 이렇게 하면 중력을 안받는 애들도 좌우에 있는 콜라이더와 충돌했을 때 위아래로 못움직임 (탑뷰)
* 중력과 관계 없이 충돌 중에도 그 테두리에서는 전방향으로 움직일 수 있게 하고싶음
* 콜라이더 쪽으로만 더이상 나아가지 못하고, 평행한 방향과 반대되는 방향으로는 이동할 수 있게끔
* 
* => 충돌 중에도 콜라이더의 평면에 맞게 미끄러져야 하고, 콜라이더 쪽으로는 더 못 가게 막되, 
     다른 방향으로는 움직일 수 있도록 하고 싶다.
     유니티처럼 콜라이더에 메타데이터를 추가해서 충돌한 면의 노말을 구할 수 있도록 할 에정
*/

class Transform;
class CircleCollider;
class BoxCollider : public ICollider
{
public:
    Transform* transform = nullptr;

    // collider
    Vector2 offset = Vector2::zero;
    Vector2 size = { 10,10 };
    
public:
    // component cycle
    BoxCollider() 
    { 
        colliderType = ColliderType::Box;
        ColliderSystem::Get().Regist(this);
    }
    ~BoxCollider() override { ColliderSystem::Get().Unregist(this); }

    void OnEnable() override;
    void UpdateBounds() override;
    bool isCollision(ICollider* other) override;
    void FinalizeCollision() override;
    void OnDestroy() override;

private:
    // collision event
    void OnCollisionEnter(ICollider* other) override;
    void OnCollisionStay(ICollider* other) override;
    void OnCollisionExit(ICollider* other) override;
    void OnTriggerEnter(ICollider* other) override;
    void OnTriggerStay(ICollider* other) override;
    void OnTriggerExit(ICollider* other) override;

    // collision cheak
    bool CheckAABBCollision(BoxCollider* other);
    bool CheakCircleCollision(CircleCollider* other);

    // 내부 체크용 (축별 이동 로직을 위한)
    bool InternalCheckCollision(ICollider* other);

public:
    // debug draw
    void DebugColliderDraw() override;
};


