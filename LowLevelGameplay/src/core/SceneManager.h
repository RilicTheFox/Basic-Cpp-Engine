#pragma once

#include "Scene.h"
#include "isScene.h"
#include "Signal.h"

namespace LLGP
{
    class SceneManager
    {
    public:
        static Signal<float> updateEvent;
        static Signal<float> fixedUpdateEvent;

        template<class T> requires isScene<T> static void ChangeScene()
        {
            m_currentScene.reset(new T());
            m_currentScene->Init();
        }

        static Scene* GetCurrentScene() { return m_currentScene.get(); }

    private:
        static std::unique_ptr<Scene> m_currentScene;
    };
}
