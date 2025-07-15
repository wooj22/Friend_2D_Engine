#include "Rigidbody.h"
#include "Transform.h"
#include "GameObject.h"
#include "Time.h"

void Rigidbody::OnEnable()
{
    transform = this->owner->GetComponent<Transform>();
}

void Rigidbody::OnDestroy()
{

}

void Rigidbody::FixedUpdate()
{
    if (!transform) return;

    // gravity, acceleration, drag
    if (useGravity) acceleration += Vector2(0, -9.8f) * gravityScale;
    velocity += acceleration * Time::GetFixedDeltaTime();
    velocity *= (1.0f - drag);      // 

    // velocity -> transform
    transform->SetPosition(transform->GetPosition() + velocity);

    acceleration = Vector2::zero;
}

void Rigidbody::AddForce(const Vector2& force)
{
    acceleration += force / mass;
}