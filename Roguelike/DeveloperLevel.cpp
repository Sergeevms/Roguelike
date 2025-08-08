#include "DeveloperLevel.h"

#include <memory>

#include "AIActor.h"
#include "BackgroundMusic.h"
#include "GameWorld.h"
#include "LabyrinthBuilder.h"
#include "PlayerActor.h"
#include "Settings.h"
#include "TransformComponent.h"

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
    auto enemyActor = std::make_shared<AIActor>(
        settings->aiParameters, exitTransform->GetWorldPosition());

    auto backgroundMusic = std::make_shared<BackgroundMusic>();
}

void DeveloperLevel::Restart() {
    Stop();
    Start();
}

void DeveloperLevel::Stop() { MaxrEngine::GameWorld::Instance()->Clear(); }
}  // namespace Roguelike