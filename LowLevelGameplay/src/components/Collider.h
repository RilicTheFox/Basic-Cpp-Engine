#pragma once
#include "core/Component.h"
#include "core/Transform.h"

namespace LLGP
{
	struct CollisionResult;
	class CircleCollider;

	class Collider : public Component
	{
	public:
		Collider(GameObject* owner);
		~Collider();

		virtual CollisionResult* IsIntersecting(Collider& other) = 0;
		virtual CollisionResult* IsIntersecting(CircleCollider& other) = 0;

	protected:
		Transform* _transform;
	};
}
