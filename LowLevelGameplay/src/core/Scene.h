#pragma once
#include <memory>
#include <vector>
#include "core/Signal.h"
#include "GameObject.h"

namespace LLGP
{
    class Scene
    {
    public:
        Scene() = default;
        virtual ~Scene() = default;

        virtual void Init();

        GameObject* CreateGameObject();
        std::vector<GameObject*> GetGameObjects();
        void DeleteQueuedObjects();

    private:
        std::vector<GameObject*> m_gameObjects;
        std::vector<GameObject*> m_deletionQueue;
        Signal<float>* m_updateEventPtr;
        Signal<float>* m_fixedUpdateEventPtr;

        void QueueForDeletion(GameObject* gameObject);
    };
}
