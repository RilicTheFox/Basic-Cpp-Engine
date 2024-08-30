#pragma once

#include "core/Scene.h"

namespace LLGP
{
    class GameplayScene : public Scene
    {
    public:
        GameplayScene() : Scene() {}
        void Init() override;
    };
}
