#include "Follower.h"
#include <Vector2.h>
#include "core/GameObject.h"

namespace LLGP
{
	void Follower::FixedUpdate(float deltaTime)
	{
		Vector2f currentPos = GetGameObject()->transform.GetPosition();
		Vector2f targetPos = target->transform.GetPosition();

		Vector2f newPos = Vector2f::Lerp(currentPos, targetPos, weight * deltaTime);

		GetGameObject()->transform.SetPosition(newPos);
	}
}
