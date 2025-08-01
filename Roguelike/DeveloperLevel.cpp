#include "DeveloperLevel.h"

#include <memory>

#include "BackgroundMusic.h"
#include "Enemy.h"
#include "GameWorld.h"
#include "LabyrinthBuilder.h"
#include "Player.h"
#include "Settings.h"
#include "TransformComponent.h"

namespace Roguelike {
void DeveloperLevel::Start() {
    auto* settings = Settings::Instance();
    LabyrinthBuilder labyrinthBuilder;
    labyrinthBuilder.Generate(settings->labyrinthParameters);
    labyrinth = labyrinthBuilder.ConstructLabyrinth();
    auto startCell = labyrinth->GetStartCell();
    auto labyrinthElements = labyrinth->GetElements();
    auto* startCellTransform =
        labyrinthElements[startCell.x][startCell.y]
            ->GetGameObject()
            ->GetComponent<MaxrEngine::TransformComponent>();
    player = std::make_shared<Player>();
    auto* playerTransform =
        player->GetGameObject()->GetComponent<MaxrEngine::TransformComponent>();
    backgroundMusic = std::make_shared<BackgroundMusic>();
    playerTransform->SetWorldPosition(startCellTransform->GetWorldPosition());
    enemy = std::make_shared<Enemy>();

    auto* enemyTransform =
        enemy->GetGameObject()->GetComponent<MaxrEngine::TransformComponent>();
    auto exitCell = labyrinth->GetExit();
    auto* exitTransform = exitCell->GetGameObject()
                              ->GetComponent<MaxrEngine::TransformComponent>();
    enemyTransform->SetWorldPosition(exitTransform->GetWorldPosition());
}

void DeveloperLevel::Restart() {
    Stop();
    Start();
}

void DeveloperLevel::Stop() { MaxrEngine::GameWorld::Instance()->Clear(); }
}  // namespace Roguelike