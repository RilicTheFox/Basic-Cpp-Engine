#include "Player.h"
#include <core/ResourceManager.h>
#include <core/SceneManager.h>
#include "Projectile.h"
#include "SpriteRenderer.h"
#include "core/GameObject.h"
#include "core/Input.h"
#include <iostream>

namespace LLGP
{
    Player::Player(GameObject* owner) : Component(owner)
    {
	    m_thrustForce = 400;
	    m_rigidBody = GetGameObject()->GetComponent<RigidBody>();
	    m_canShoot = true;

	    m_shootTimer.TimeOut.AddListener(this, std::bind(&Player::OnShootTimerTimeout, this));
    }

    void Player::Update(float deltaTime)
    {
		Vector2f input = Input::GetThrustInput();
		m_rigidBody->AddForce(input * m_thrustForce * deltaTime, Force);

		if (input.GetMagnitude() > 0)
		{
			GetGameObject()->transform.SetUp(input);
		}

    	if (Input::IsActionPressed("shoot"))
    	{
    		Shoot();
    	}
    }

    void Player::OnCollisionEnter(CollisionResult* collision)
    {
	    std::cout << "ENTER" << std::endl;
    }

    void Player::OnCollisionStay(CollisionResult* collision)
    {
    	std::cout << "STAY" << std::endl;
    }

    void Player::OnCollisionExit(CollisionResult* collision)
    {
    	std::cout << "EXIT" << std::endl;
    }

    void Player::Shoot()
    {
    	if (m_canShoot == false) return;

    	CreateProjectile();

    	// Start timer
    	m_shootTimer.Start();
    	m_canShoot = false;
    }

    void Player::CreateProjectile()
    {
    	GameObject* laser = SceneManager::GetCurrentScene()->CreateGameObject();
    	laser->SetName("laser");
    	laser->AddComponent<Projectile>();
    	laser->GetComponent<Projectile>()->speed = 300;
    	laser->GetComponent<Projectile>()->instigator = GetGameObject();
    	laser->AddComponent<SpriteRenderer>();
    	laser->AddComponent<SpriteRenderer>()->SetTexture(ResourceManager::GetTexture("assets/textures/laser.png"));
    	laser->AddComponent<CircleCollider>();
    	laser->GetComponent<CircleCollider>()->radius = 4;
    	laser->transform.SetRotation(GetGameObject()->transform.GetRotation());
    	laser->transform.SetPosition(GetGameObject()->transform.GetPosition());
    }

    void Player::OnShootTimerTimeout()
    {
    	m_canShoot = true;
    }
}
