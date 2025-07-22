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

    if (!isKinematic)
    {
        // impulse
        velocity += impulse / mass;

        // gravity
        if (useGravity && !isGrounded) acceleration += Vector2(0, -9.8f) * gravityScale;

        // acceleration
        velocity += acceleration * Time::GetFixedDeltaTime();
        velocity *= (1.0f - drag);

        // block
        if (isBlockedLeft && velocity.x < 0) velocity.x = 0;
        if (isBlockedRight && velocity.x > 0) velocity.x = 0;
        if (isBlockedDown && velocity.y < 0) velocity.y = 0;
        if (isBlockedUp && velocity.y > 0) velocity.y = 0;

        // grounded
        if (isGrounded && useGravity && velocity.y < 0) velocity.y = -1;

        // position update
        transform->SetPosition(transform->GetPosition() + velocity * Time::GetFixedDeltaTime());

        // reset
        impulse = Vector2::zero;
        acceleration = Vector2::zero;
    } 
}

void Rigidbody::AddForce(const Vector2& force)
{
    acceleration += force / mass;
}

void Rigidbody::AddImpulse(const Vector2& impulse) 
{
    this->impulse = impulse / mass;
}
