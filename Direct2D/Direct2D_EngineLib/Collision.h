#pragma once
#include "ICollider.h"
#include "Vector2.h"

/* [Collision]
* 물리 충돌 이벤트의 block을 구현하기 위해 추가한 충돌 관련 data class
* OnCollisionEnter, Stay, Eixt는 충돌 발생시 collider객체만이 아닌 
* 여러 충돌 데이터가 담긴 Collistion객체를 전달하며, 이를 통해 충돌 방향을 알아내 block을 수행한다.
*/

// 일단 Contect Info로 해볼거. 이거 안씀!

//class Collision
//{
//private:
//    ICollider* thisCollider = nullptr;    // this collider
//
//public:
//    ICollider* otherCollider = nullptr;   // other collider
//    Vector2 contactPoint;                 // 충돌 지점
//    Vector2 contactNormal;                // 충돌 법선
//    Vector2 relativeVelocity;             // 상대 속도
//
//    Collision(ICollider* _this, ICollider* other) 
//        : thisCollider(_this), otherCollider(other) { }
//
//
//};
//
