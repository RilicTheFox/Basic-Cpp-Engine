#include "RigidBody.h"
#include <core/GameObject.h>

namespace LLGP
{
	RigidBody::RigidBody(GameObject* owner) : Component(owner)
	{
		mass = 1;
		damp = 0;

		m_force = Vector2f::zero;
		m_acceleration = Vector2f::zero;
		m_impulse = Vector2f::zero;
		m_velocity = Vector2f::zero;
	}

	void RigidBody::FixedUpdate(float fixedDeltaTime)
	{
		// Accumulate added forces
		Vector2f newForce;

		// Force
		newForce += m_force * fixedDeltaTime / mass;
		// Acceleration
		newForce += m_acceleration * fixedDeltaTime;
		// Impulse
		newForce += m_impulse / mass;

		m_force = Vector2f::zero;
		m_acceleration = Vector2f::zero;
		m_impulse = Vector2f::zero;

		// Add force to velocity
		m_velocity += newForce;

		// Add damp - Thanks Godot!
		float tDamp = 1.0 - damp * fixedDeltaTime;
		m_velocity *= tDamp;

		// Apply velocity
		Vector2f currentPos = GetGameObject()->transform.GetPosition();
		GetGameObject()->transform.SetPosition(currentPos + m_velocity);
	}

	void RigidBody::OnCollisionEnter(CollisionResult* collision)
	{
		// If no rigidbody found on other collider, do not resolve - it is for detection only.
		if (collision->otherCollider->GetGameObject()->GetComponent<RigidBody>() == nullptr) return;

		// Resolve collision
		Vector2f translation = (collision->impactNormal * collision->penetrationDepth) / 2;
		translation *= 1.001;
		Vector2f pos = GetGameObject()->transform.GetPosition();
		GetGameObject()->transform.SetPosition(pos + translation);

		// Add bounce force
		Vector2f force = collision->impactNormal;
		float magnitude = 2;
		force *= magnitude;

		AddForce(force, Impulse);
	}

	void RigidBody::AddForce(Vector2f addedForce, ForceMode mode)
	{
		switch (mode)
		{
		case Force:
			m_force += addedForce;
			break;
		case Acceleration:
			m_acceleration += addedForce;
			break;
		case Impulse:
			m_impulse += addedForce;
			break;
		}
	}
}
