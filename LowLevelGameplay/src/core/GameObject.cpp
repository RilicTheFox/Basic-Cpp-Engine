#include "GameObject.h"
#include "SceneManager.h"
#include "Signal.h"

namespace LLGP
{
    GameObject::GameObject(): m_name("GameObject"), m_isActive(false), m_components(std::vector<std::unique_ptr<Component>>()), m_isQueuedForDeletion(false)
    {
        SceneManager::updateEvent.AddListener(this, std::bind(&GameObject::UpdateComponments, this, std::placeholders::_1));
        SceneManager::fixedUpdateEvent.AddListener(this, std::bind(&GameObject::FixedUpdateComponments, this, std::placeholders::_1));
    }

    GameObject::~GameObject()
    {
        SceneManager::updateEvent.RemoveListener(this, std::bind(&GameObject::UpdateComponments, this, std::placeholders::_1));
        SceneManager::fixedUpdateEvent.RemoveListener(this, std::bind(&GameObject::FixedUpdateComponments, this, std::placeholders::_1));
    }

    void GameObject::Destroy()
    {
		if (m_isQueuedForDeletion == true) return;

		m_isQueuedForDeletion = true;
        DeletionQueued.Emit(this);
    }

    void GameObject::UpdateComponments(float deltaTime) const
    {
        for (int i = 0; i < m_components.size(); i++)
        {
            m_components[i]->Update(deltaTime);
        }
    }

    void GameObject::FixedUpdateComponments(float fixedDeltaTime) const
    {
        for (int i = 0; i < m_components.size(); i++)
        {
            m_components[i]->FixedUpdate(fixedDeltaTime);
        }
    }
}
