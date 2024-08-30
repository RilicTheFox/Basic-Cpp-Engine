#include "Scene.h"

namespace LLGP
{
	void Scene::Init()
	{
		m_gameObjects = std::vector<GameObject*>();
	}

	GameObject* Scene::CreateGameObject()
    {
		GameObject* newGameObject = new GameObject();
		m_gameObjects.push_back(newGameObject);
		newGameObject->DeletionQueued.AddListener(this, std::bind(&Scene::QueueForDeletion, this, std::placeholders::_1));
		return m_gameObjects.back();
    }

	std::vector<GameObject*> Scene::GetGameObjects()
	{
		return m_gameObjects;
	}

	void Scene::DeleteQueuedObjects()
	{
		for (int i = 0; i < m_deletionQueue.size(); i++)
		{
			delete m_deletionQueue[i];
 			m_gameObjects.erase(std::find(m_gameObjects.begin(), m_gameObjects.end(), m_deletionQueue[i]));
		}

		m_deletionQueue.clear();
	}

	void Scene::QueueForDeletion(GameObject* gameObject)
	{
		m_deletionQueue.push_back(gameObject);
	}
}
