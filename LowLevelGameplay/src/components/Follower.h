#pragma once
#include "core/Component.h"

namespace LLGP
{
	class Follower : public Component
	{
	public:
		Follower(GameObject* owner) : Component(owner) {}

		float weight = 3;
		GameObject* target;

		void FixedUpdate(float deltaTime) override;
	};
}
