#include "DeveloperLevel.h"

#include <memory>
#include <vector>

#include "AIActor.h"
#include "AIActorManagerSystem.h"
#include "BackgroundMusic.h"
#include "GameWorld.h"
#include "LabyrinthBuilder.h"
#include "MovementComponent.h"
#include "PlayerActor.h"
#include "Settings.h"
#include "SpriteRendererComponent.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace Roguelike {
void DeveloperLevel::Start() {
    auto* settings = Settings::Instance();
    LabyrinthBuilder labyrinthBuilder;
    labyrinthBuilder.Generate(settings->labyrinthParameters);
    auto labyrinth = labyrinthBuilder.ConstructLabyrinth();
    auto startCell = labyrinth->GetStartCell();
    auto labyrinthElements = labyrinth->GetElements();
    auto* startCellTransform =
        labyrinthElements[startCell.x][startCell.y]
            ->GetGameObject()
            ->GetComponent<MaxrEngine::TransformComponent>();
    auto playerActor = std::make_shared<PlayerActor>(
        settings->playerParameters, startCellTransform->GetWorldPosition());

    auto& exitCell = labyrinth->GetExit();
    auto* exitTransform = exitCell->GetGameObject()
                              ->GetComponent<MaxrEngine::TransformComponent>();
    std::vector<MaxrEngine::Vector2Df> oneSpawn = {
        exitTransform->GetWorldPosition()};
    std::vector<MaxrEngine::Vector2Df> generationDeadEnds;
    for (auto deadEnd : labyrinth->GetGenerationDeadEnds()) {
        generationDeadEnds.push_back(labyrinth->GetCellCoordinates(deadEnd));
    }
    auto makeEnemyFastAndRed = [](std::shared_ptr<AIActor> actor) {
        auto* sprite =
            actor->GetGameObject()
                ->GetComponent<MaxrEngine::SpriteRendererComponent>();
        sprite->SetColor(sf::Color::Red);
        auto* movement = actor->GetGameObject()
                             ->GetComponent<MaxrEngine::MovementComponent>();
        movement->SetSpeed(movement->GetSpeed() * 3);
    };
    auto spawner = AIActorManagerSystem::Instance();

    spawner->SpawnRandomly(settings->aiParameters, oneSpawn, 6);

    auto backgroundMusic = std::make_shared<BackgroundMusic>();
}

void DeveloperLevel::Restart() {
    Stop();
    Start();
}

void DeveloperLevel::Stop() { MaxrEngine::GameWorld::Instance()->Clear(); }
}  // namespace Roguelike