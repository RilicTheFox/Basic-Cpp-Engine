#include <chrono>
#include <SFML/Graphics.hpp>
#include "scenes/GameplayScene.h"
#include "core/SceneManager.h"
#include "core/Renderer.h"
#include "core/Physics.h"
#include "core/Input.h"

#define FIXEDDELTATIME 0.016666667

using namespace LLGP;

int main()
{
	Renderer::Init();
	Input::Init();

    // Delta Time
    float deltaTime;
    float timeSincePhysicsStep = 0;
    std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();

    // Initialise the first scene
    SceneManager::ChangeScene<GameplayScene>();

    while (Renderer::GetRenderWindow()->isOpen())
    {
    	SceneManager::GetCurrentScene()->DeleteQueuedObjects();

		// Get input
		Input::Poll();

        // Delta Time
        // - Find the new time
        std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
        // - Get the number of microseconds between then and now, and divide by 1,000,000 to get seconds.
        deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - lastTime).count() / 1000000.f;
        lastTime = now;

		// Update!
		SceneManager::updateEvent.Emit(deltaTime);

        // Physics step
        timeSincePhysicsStep += deltaTime;
        while (timeSincePhysicsStep > FIXEDDELTATIME)
        {
			Physics::CollectCollisions();
        	Physics::SendColliionEvents();

            SceneManager::fixedUpdateEvent.Emit(FIXEDDELTATIME);

            // Reduce the physics step by the fixed delta time.
            timeSincePhysicsStep -= FIXEDDELTATIME;
        }

        sf::Event event{};
        while (Renderer::GetRenderWindow()->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
				Renderer::GetRenderWindow()->close();
        }

        Renderer::Draw();
    }

    return 0;
}
