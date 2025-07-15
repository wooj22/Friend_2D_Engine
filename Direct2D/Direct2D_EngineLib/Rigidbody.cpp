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

    // gravity
    if (useGravity) 
    {
        acceleration += Vector2(0, -9.8f) * gravityScale;
    }

    // apply acceleration
    velocity += acceleration * Time::GetFixedDeltaTime();
    velocity *= (1.0f - drag);

    // block
    //if (blockX) { velocity.x = 0; blockX = false; }
    //if (blockY) { velocity.y = 0; blockY = false; }

    // position update
    transform->SetPosition(transform->GetPosition() + velocity);

    // reset acceleration
    acceleration = Vector2::zero;
}

void Rigidbody::AddForce(const Vector2& force)
{
    acceleration += force / mass;
}