#include "pch.h"
#include "Engine.h"
#include <SFML/Graphics.hpp>
#include "RenderSystem.h"
#include "GameWorld.h"

namespace MaxrEngine
{
	Engine::Engine()
	{
		unsigned int seed = static_cast<unsigned int>(time(nullptr));
		srand(seed);
	}

	Engine* Engine::Instance()
	{
		static Engine instance;
		return &instance;
	}

	void Engine::Run()
	{
		LOG_INFO("Engine runned");
		sf::Clock gameClock;
		sf::Event event;

		while (RenderSystem::Instance()->GetMainWindow().isOpen())
		{
			sf::Time dt = gameClock.restart();
			float deltaTime = dt.asSeconds();

			while (RenderSystem::Instance()->GetMainWindow().pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					RenderSystem::Instance()->GetMainWindow().close();
				}
			}

			if (!RenderSystem::Instance()->GetMainWindow().isOpen())
			{
				break;
			}

			RenderSystem::Instance()->GetMainWindow().clear();

			GameWorld::Instance()->Update(deltaTime);
			GameWorld::Instance()->FixedUpdate(deltaTime);
			GameWorld::Instance()->Render();
			GameWorld::Instance()->LateUpdate();

			RenderSystem::Instance()->GetMainWindow().display();
		}
		GameWorld::Instance()->Clear();
		LOG_INFO("Engine stopped");
	}
}
