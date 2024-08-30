#include "CircleCollider.h"
#include "core/Physics.h"

namespace LLGP
{
	CollisionResult* CircleCollider::IsIntersecting(CircleCollider& other)
	{
		return Physics::Intersection_CircleToCircle(*this, other);
	}
}
