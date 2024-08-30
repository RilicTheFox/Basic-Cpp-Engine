#include "Projectile.h"
#include "core/GameObject.h"

namespace LLGP
{
    Projectile::Projectile(GameObject* owner): Component(owner)
    {
        m_lifeTimer.TimeOut.AddListener(this, std::bind(&Projectile::OnLifeTimerTimeout, this));
        m_lifeTimer.Start();
    }

    Projectile::~Projectile()
    {
        m_lifeTimer.TimeOut.RemoveListener(this, std::bind(&Projectile::OnLifeTimerTimeout, this));
    }

    void Projectile::Start()
    {
        m_lifeTimer.Start();
    }

    void Projectile::FixedUpdate(float fixedDeltaTime)
    {
        Transform* tf = &GetGameObject()->transform;
        tf->SetPosition(tf->GetPosition() + tf->GetUp() * speed * fixedDeltaTime);
    }

    void Projectile::OnCollisionEnter(CollisionResult* collision)
    {
        if (collision->otherCollider->GetGameObject() == instigator) return;
        GetGameObject()->Destroy();
    }

    void Projectile::OnLifeTimerTimeout()
    {
        GetGameObject()->Destroy();
    }
}
