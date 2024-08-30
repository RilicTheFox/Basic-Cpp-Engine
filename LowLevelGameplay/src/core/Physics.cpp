#include "Physics.h"
#include <algorithm>

namespace LLGP
{
	std::vector<Collider*> Physics::m_colliders;
	std::vector<CollisionResult*> Physics::m_collisionResults;
	std::vector<CollisionResult*> Physics::m_oldCollisionResults;

	void Physics::CollectCollisions()
	{
		m_collisionResults.clear();

		// Loop through every collider.
		for (int i = 0; i < m_colliders.size(); i++)
		{
			for (int j = 0; j < m_colliders.size(); j++)
			{
				if (i == j) continue;

				CollisionResult* col = m_colliders[i]->IsIntersecting(*m_colliders[j]);
				if (col == nullptr) continue;

				m_collisionResults.push_back(col);
			}
		}
	}

	void Physics::SendColliionEvents()
	{
		// Store a copy of the old result list that will be whittled down to the colliders that aren't accounted for to
		// send EXIT events to.
		std::vector<CollisionResult*> exitList = m_oldCollisionResults;

		// Loop through and compare the results' colliders from the back of both vectors.
		for (int i = m_collisionResults.size() - 1; i >= 0; i--)
		{
			// If, empty just break.
			if (m_collisionResults.empty()) break;

			CollisionResult* newResult = m_collisionResults[i];

			// If empty, just call ENTER and continue.
			if (exitList.empty())
			{
				newResult->thisCollider->GetGameObject()->OnCollisionEnter.Emit(newResult);
				continue;
			}

			for (int j = exitList.size() - 1; j >= 0; j--)
			{

				CollisionResult* oldResult = exitList[j];

				// If colliders don't match or is null, continue. This is not the right collision result.
				bool isNotMatch = newResult->thisCollider != oldResult->otherCollider and newResult->otherCollider != oldResult->otherCollider;
				bool isNull = oldResult == nullptr;

				if (isNotMatch or isNull)
				{
					// If this is the last one in the loop, then the collision is new. Send the ENTER signal.
					if (i == 0) newResult->thisCollider->GetGameObject()->OnCollisionEnter.Emit(newResult);
					continue;
				}

				// If this point is reached, they match. Send STAY event to this collision's instigator.
				newResult->thisCollider->GetGameObject()->OnCollisionStay.Emit(newResult);

				// Remove item from the exit list.
				exitList.erase(exitList.begin() + j);
			}
		}

		// After this algorithm finishes, loop through the remaining collision results in the list and send the EXIT
		// signal.
		for (int i = 0; i < exitList.size(); i++)
		{
			if (exitList[i] == nullptr) break;

			auto itr = std::find(m_colliders.begin(), m_colliders.end(), exitList[i]->thisCollider);
			if (itr == m_colliders.end()) break;

			exitList[i]->thisCollider->GetGameObject()->OnCollisionExit.Emit(exitList[i]);
		}

		// Set the *real* old collisions vector to the new one.
		for (CollisionResult* col : m_oldCollisionResults)
		{
			delete col;
		}

		m_oldCollisionResults = m_collisionResults;
	}

	void Physics::UpdatePhysics()
	{
		// placeholder?????????
	}

	void Physics::RegisterCollider(Collider* collider)
	{
		if (std::find(m_colliders.begin(), m_colliders.end(), collider) == m_colliders.end())
		{
			m_colliders.push_back(collider);
		}
	}

	void Physics::DeregisterCollider(Collider* collider)
	{
		auto itr = std::find(m_colliders.begin(), m_colliders.end(), collider);

		if (itr != m_colliders.end())
		{
			m_colliders.erase(itr);
		}
	}

	CollisionResult* Physics::Intersection_CircleToCircle(CircleCollider& a, CircleCollider& b)
	{
		Vector2f diff = b.GetGameObject()->transform.GetPosition() - a.GetGameObject()->transform.GetPosition();
		float radiiSum = b.radius + a.radius;

		// If no collision, return nullptr.
		if (diff.GetMagnitude() > radiiSum) return nullptr;

		// Calculate collision point
		Vector2f collisionPoint = a.GetGameObject()->transform.GetPosition();
		collisionPoint.Normalise();
		collisionPoint *= a.radius;
		collisionPoint = a.GetGameObject()->transform.GetPosition() + collisionPoint;

		// Get normal
		Vector2f normal = -diff.Normalised();

		// Get pen depth
		float penetrationDepth = fabs(diff.GetMagnitude() - radiiSum);

		CollisionResult* result = new CollisionResult;
		result->thisCollider = &a;
		result->otherCollider = &b;
		result->collisionPoint = collisionPoint;
		result->impactNormal = normal;
		result->penetrationDepth = penetrationDepth;

		return result;
	}
}
