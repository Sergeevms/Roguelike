#include "pch.h"

#include "Engine.h"

#include <cstdlib>
#include <ctime>

#include "SFML/System/Clock.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"

#include "GameWorld.h"
#include "Logger.h"
#include "RenderSystem.h"

namespace MaxrEngine {
Engine::Engine() {
    const unsigned int seed = static_cast<unsigned int>(time(nullptr));
    srand(seed);
}

Engine* Engine::Instance() {
    static Engine instance;
    return &instance;
}

void Engine::Run() {  // NOLINT
    LOG_INFO("Engine runned");
    sf::Clock gameClock;
    sf::Event event;

    while (RenderSystem::Instance()->GetMainWindow().isOpen()) {
        const sf::Time timeElapsed = gameClock.restart();
        const float deltaTime = timeElapsed.asSeconds();

        while (RenderSystem::Instance()->GetMainWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                RenderSystem::Instance()->GetMainWindow().close();
            }
        }

        if (!RenderSystem::Instance()->GetMainWindow().isOpen()) {
            GameWorld::Instance()->ClearImmediate();
            break;
        }

        RenderSystem::Instance()->GetMainWindow().clear();

        GameWorld::Instance()->Update(deltaTime);
        GameWorld::Instance()->FixedUpdate(deltaTime);
        GameWorld::Instance()->Render();
        GameWorld::Instance()->LateUpdate();

        RenderSystem::Instance()->GetMainWindow().display();
    }
    LOG_INFO("Engine stopped");
}
}  // namespace MaxrEngine
