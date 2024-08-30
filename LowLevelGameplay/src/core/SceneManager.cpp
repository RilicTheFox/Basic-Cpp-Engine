#include <core/SceneManager.h>

namespace LLGP
{
    Signal<float> SceneManager::updateEvent;
    Signal<float> SceneManager::fixedUpdateEvent;
    std::unique_ptr<Scene> SceneManager::m_currentScene;
}
