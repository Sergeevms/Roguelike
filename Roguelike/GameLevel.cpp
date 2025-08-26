#include "GameLevel.h"

#include <memory>
#include <vector>

#include "AIActorManagerSystem.h"
#include "GameWorld.h"
#include "Labyrinth.h"
#include "LabyrinthBuilder.h"
#include "PlayerActor.h"
#include "Settings.h"
#include "Vector.h"
namespace Roguelike {
GameLevel::GameLevel(const Parameters& parameters) : parameters(parameters) {};
void GameLevel::Start() {
    auto settings = Settings::Instance();
    // Build labyrinth
    auto builder = std::make_unique<LabyrinthBuilder>();
    builder->Generate(parameters.builderParameters);
    labyrinth = builder->ConstructLabyrinth();

    // Get dead ends from labyrinth generation
    std::vector<MaxrEngine::Vector2Df> generationDeadEnds;
    for (const auto& deadEnd : labyrinth->GetGenerationDeadEnds()) {
        generationDeadEnds.push_back(labyrinth->GetCellCoordinates(deadEnd));
    }
    // Spawn enemies at dead ends
    auto spawner = AIActorManagerSystem::Instance();
    spawner->Reset(labyrinth->GetLabyrinthCoodinatesRect());
    spawner->SpawnRandomly(settings->aiParameters, generationDeadEnds,
                           parameters.enemyCount);

    auto startCell = labyrinth->GetCellCoordinates(labyrinth->GetStartCell());
    player =
        std::make_shared<PlayerActor>(settings->playerParameters, startCell);
}
void GameLevel::Restart() {
    Stop();
    Start();
}
void GameLevel::Stop() {
    player = nullptr;
    labyrinth = nullptr;
    MaxrEngine::GameWorld::Instance()->Clear();
}
std::shared_ptr<PlayerActor> GameLevel::GetPlayer() { return player; }
std::shared_ptr<Labyrinth> GameLevel::GetLabyrinth() { return labyrinth; }
}  // namespace Roguelike