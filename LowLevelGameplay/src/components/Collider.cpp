#include "Collider.h"
#include "core/GameObject.h"
#include "core/Physics.h"

namespace LLGP
{
	Collider::Collider(GameObject* owner) : Component(owner)
	{
		_transform = &GetGameObject()->transform;
		Physics::RegisterCollider(this);
	}

	Collider::~Collider()
	{
		Physics::DeregisterCollider(this);
	}
}
