#pragma once
#include <string>
#include <vector>
#include <memory>
#include <core/Component.h>
#include <core/Object.h>
#include <core/isComponent.h>
#include <core/Transform.h>
#include "core/Signal.h"
#include "core/Physics.h"

namespace LLGP
{
	class GameObject : Object
	{
	public:
		GameObject();
		GameObject(const GameObject&) = default;
		~GameObject();

		Transform transform{};

		Signal<GameObject*> DeletionQueued;

		Signal<CollisionResult*> OnCollisionEnter;
		Signal<CollisionResult*> OnCollisionStay;
		Signal<CollisionResult*> OnCollisionExit;

		void Destroy();

		inline void SetName(std::string newName) { m_name = newName; }
		inline std::string GetName() { return m_name; }

		void SetActive(bool newActive) { m_isActive = newActive; };
		inline bool GetActive() { return m_isActive; }

		inline void SetTag(std::string newTag) { m_tag = newTag; }
		inline bool CompareTag(std::string comp) { return m_tag == comp; }

		inline std::vector<std::unique_ptr<Component>>* GetComponents() { return &m_components; }

		template<class T> requires isComponent<T> T* GetComponent()
		{
			T* returnComp = nullptr;
			for (const std::unique_ptr<Component> & component : m_components)
			{
				returnComp = dynamic_cast<T*>(component.get());
				if (returnComp != nullptr)
				{
					break;
				}
			}

			return returnComp;
		}

		template<class T> requires isComponent<T> T* AddComponent()
		{
			std::unique_ptr<Component> newComp = std::make_unique<T>(this);
			m_components.push_back(std::move(newComp));
			return static_cast<T*>(m_components.back().get());
		}

		template<class T> requires isComponent<T> bool RemoveComponent(T* comp)
		{
			T* returnComp = nullptr;
			for (int i = 0; i < m_components.size(); i++)
			{
				returnComp = static_cast<T*>(m_components[i].get());
				if (returnComp != nullptr)
				{
					m_components.erase(m_components.begin() + i);
					return true;
				}
			}

			return false;
		}

	private:
		std::string m_name;
		bool m_isActive;
		std::string m_tag;
		std::vector<std::unique_ptr<Component>> m_components;
		bool m_isQueuedForDeletion;

		void UpdateComponments(float deltaTime) const;
		void FixedUpdateComponments(float fixedDeltaTime) const;
	};
}



