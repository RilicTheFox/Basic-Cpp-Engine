#pragma once
#include "components/Collider.h"

namespace LLGP
{
	class CircleCollider : public Collider
	{
	public:
		float radius = 10.f;

		explicit CircleCollider(GameObject* owner) : Collider(owner) {}

		CollisionResult* IsIntersecting(Collider& other) override
		{
			return other.IsIntersecting(*this);
		}

		CollisionResult* IsIntersecting(CircleCollider& other) override;
	};
}
