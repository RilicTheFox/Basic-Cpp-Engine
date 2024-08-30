#pragma once
#include <core/Component.h>
#include "RigidBody.h"
#include "core/Timer.h"

namespace LLGP
{
    class Player : public Component
    {
    public:
        explicit Player(GameObject* owner);

        void Update(float deltaTime) override;
        void OnCollisionEnter(CollisionResult* collision) override;
        void OnCollisionStay(CollisionResult* collision) override;
        void OnCollisionExit(CollisionResult* collision) override;


        void Shoot();
        void CreateProjectile();

    private:
        void OnShootTimerTimeout();

        RigidBody* m_rigidBody;
        float m_thrustForce;
        float m_shootRate = 0.2;
        Timer m_shootTimer = Timer(m_shootRate, true);
        bool m_canShoot;
    };

}
