#include "DeveloperLevel.h"

#include <memory>
#include <vector>

#include "AIActorManagerSystem.h"
#include "BackgroundMusic.h"
#include "GameWorld.h"
#include "LabyrinthBuilder.h"
#include "PlayerActor.h"
#include "Settings.h"
#include "Vector.h"

namespace Roguelike {
constexpr int enemyCount = 4;
void DeveloperLevel::Start() {
    auto* settings = Settings::Instance();
    // Construct labyrinth
    LabyrinthBuilder labyrinthBuilder;
    labyrinthBuilder.Generate(settings->labyrinthParameters);
    auto labyrinth = labyrinthBuilder.ConstructLabyrinth();
    // Get start cell and create player at it
    auto& startCell = labyrinth->GetStartCell();
    auto playerActor = std::make_shared<PlayerActor>(
        settings->playerParameters, labyrinth->GetCellCoordinates(startCell));
    // Get dead ends from labyrinth generation
    std::vector<MaxrEngine::Vector2Df> generationDeadEnds;
    for (const auto& deadEnd : labyrinth->GetGenerationDeadEnds()) {
        generationDeadEnds.push_back(labyrinth->GetCellCoordinates(deadEnd));
    }
    // Spawn enemies at dead ends
    auto spawner = AIActorManagerSystem::Instance();
    spawner->Reset(labyrinth->GetLabyrinthCoodinatesRect());
    spawner->SpawnRandomly(settings->aiParameters, generationDeadEnds,
                           enemyCount);

    auto backgroundMusic = std::make_shared<BackgroundMusic>();
}

void DeveloperLevel::Restart() {
    Stop();
    Start();
}

void DeveloperLevel::Stop() { MaxrEngine::GameWorld::Instance()->Clear(); }
}  // namespace Roguelike