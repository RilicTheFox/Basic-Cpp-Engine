#pragma once
#include "core/Component.h"
#include "Vector2.h"

namespace LLGP
{
	enum ForceMode
	{
		Force,
		Acceleration,
		Impulse,
	};

	class RigidBody : public Component
	{
	public:
		float mass = 1;
		float damp = 0;

		explicit RigidBody(GameObject* owner);
		~RigidBody() = default;

		void FixedUpdate(float fixedDeltaTime) override;

		void OnCollisionEnter(CollisionResult* collision) override;

		void AddForce(Vector2f addedForce, ForceMode mode);

		Vector2f GetVelocity() { return m_velocity; }

	private:
		Vector2f m_force = Vector2f::zero;
		Vector2f m_acceleration = Vector2f::zero;
		Vector2f m_impulse = Vector2f::zero;

		Vector2f m_velocity = Vector2f::zero;
	};
}
