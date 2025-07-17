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

    // impulse
    velocity += impulse / mass;

    // gravity
    if (useGravity)
    {
        acceleration += Vector2(0, -9.8f) * gravityScale;
    }

    // acceleration
    velocity += acceleration * Time::GetFixedDeltaTime();
    velocity *= (1.0f - drag);

    // grounded
    if (isGrounded && velocity.y < 0)
    {
        velocity.y = -1;
    }

    // block
    //if (blockX) { velocity.x = 0; blockX = false; }
    //if (blockY) { velocity.y = 0; blockY = false; }

    // position update
    transform->SetPosition(transform->GetPosition() + velocity * Time::GetFixedDeltaTime());

    // reset
    impulse = Vector2::zero;
    acceleration = Vector2::zero;
}

void Rigidbody::AddForce(const Vector2& force)
{
    acceleration += force / mass;
}

void Rigidbody::AddImpulse(const Vector2& impulse) 
{
    this->impulse = impulse / mass;
}
