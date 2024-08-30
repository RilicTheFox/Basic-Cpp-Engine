#pragma once
#include "core/Component.h"
#include "core/Timer.h"

namespace LLGP {

    class GameObject;

    class Projectile : public Component
    {
    public:
        explicit Projectile(GameObject* owner);
        ~Projectile();

        GameObject* instigator;

        float speed = 10;
        float lifeSpan = 3;

        void Start() override;
        void FixedUpdate(float deltaTime) override;

        void OnCollisionEnter(CollisionResult* collision) override;

    private:
        Timer m_lifeTimer = Timer(lifeSpan, true);

        void OnLifeTimerTimeout();
    };

}
