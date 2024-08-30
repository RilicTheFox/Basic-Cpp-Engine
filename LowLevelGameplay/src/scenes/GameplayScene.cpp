#include "GameplayScene.h"
#include "components/SpriteRenderer.h"
#include "core/ResourceManager.h"
#include <components/RigidBody.h>
#include "components/Player.h"
#include <components/Camera.h>
#include "components/Follower.h"

namespace LLGP
{
    void GameplayScene::Init()
    {
		GameObject* background = CreateGameObject();
		background->AddComponent<SpriteRenderer>();
		background->GetComponent<SpriteRenderer>()->SetTexture(ResourceManager::GetTexture("assets/textures/background.png"));
		background->GetComponent<SpriteRenderer>()->GetTexture()->setRepeated(true);
		Vector2u size = Vector2u(background->GetComponent<SpriteRenderer>()->GetTexture()->getSize());
		background->GetComponent<SpriteRenderer>()->SetTextureRect(sf::IntRect(sf::Vector2i(0,0), size * 1000000));
		background->transform.SetPosition(Vector2f(-500, -500));
		
        GameObject* player = CreateGameObject();
        player->transform.SetPosition(Vector2f(20, 0));

		RigidBody* rb = player->AddComponent<RigidBody>();
        rb->damp = 2;

        player->AddComponent<Player>();
    	player->AddComponent<CircleCollider>();

		
		GameObject* placeholderShip = CreateGameObject();
    	placeholderShip->AddComponent<CircleCollider>();
		placeholderShip->AddComponent<SpriteRenderer>();
    	placeholderShip->GetComponent<SpriteRenderer>()->SetTexture(ResourceManager::GetTexture("assets/textures/ship.png"));
    	placeholderShip->GetComponent<CircleCollider>()->radius = placeholderShip->GetComponent<SpriteRenderer>()->GetTexture()->getSize().x / 2;
    	placeholderShip->AddComponent<RigidBody>();
    	placeholderShip->GetComponent<RigidBody>()->damp = 2;

    	player->AddComponent<SpriteRenderer>();
    	player->GetComponent<SpriteRenderer>()->SetTexture(ResourceManager::GetTexture("assets/textures/ship.png"));
    	player->GetComponent<CircleCollider>()->radius = player->GetComponent<SpriteRenderer>()->GetTexture()->getSize().x / 2;

		GameObject* camera = CreateGameObject();
		camera->AddComponent<Camera>();
		camera->GetComponent<Camera>()->SetZoom(0.33333333333333333333333333333333333333333333);
		camera->AddComponent<Follower>();
    	camera->GetComponent<Follower>()->target = player;
    }
}
