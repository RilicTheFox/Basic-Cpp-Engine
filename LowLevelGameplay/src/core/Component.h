#pragma once
#include <core/Object.h>

namespace LLGP
{
	class GameObject;
	class CollisionResult;

	class Component : public Object
	{
	public:
		explicit Component(GameObject* owner);
		virtual ~Component() = default;

		GameObject* GetGameObject() { return _gameObject; }

		virtual void OwnerActiveChange(bool newActive) {}
		virtual void Start() {}
		virtual void Update(float deltaTime) {}
		virtual void FixedUpdate(float fixedDeltaTime) {}
		virtual void OnEnable() {}
		virtual void OnDisable() {}

		virtual void OnCollisionEnter(CollisionResult* collision) {}
		virtual void OnCollisionStay(CollisionResult* collision) {}
		virtual void OnCollisionExit(CollisionResult* collision) {}

	protected:
		GameObject* _gameObject;
	};
}
