#pragma once
#include "components/CircleCollider.h"
#include "GameObject.h"

namespace LLGP
{
	struct CollisionResult
	{
		Collider* thisCollider;
		Collider* otherCollider;
		Vector2f impactNormal;
		Vector2f collisionPoint;
		float penetrationDepth;
	};

	class Physics
	{
	public:
		static void CollectCollisions();
		static void SendColliionEvents();
		static void UpdatePhysics();

		static void RegisterCollider(Collider* collider);
		static void DeregisterCollider(Collider* collider);

		static CollisionResult* Intersection_CircleToCircle(CircleCollider& a, CircleCollider& b);

	private:
		static std::vector<Collider*> m_colliders;
		static std::vector<CollisionResult*> m_collisionResults;
		static std::vector<CollisionResult*> m_oldCollisionResults;
	};
}
