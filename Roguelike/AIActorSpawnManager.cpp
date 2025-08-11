#include "AIActorSpawnManager.h"

#include <cstdlib>
#include <ctime>
#include <functional>
#include <memory>
#include <vector>

#include "AIActor.h"
#include "HealthComponent.h"
#include "IObserver.h"
#include "Vector.h"

namespace Roguelike {
static const std::vector<MaxrEngine::Vector2Df> offsets = {
    {0, 0}, {1, 0}, {1, 1}, {0, 1}, {-1, 0}, {-1, -1}, {0, -1}};
void AIActorSpawnManager::Spawn(
    const AIActor::Parameters& actorParameters,
    const std::vector<MaxrEngine::Vector2Df>& spawnPositions, const int count,
    const std::function<void(std::shared_ptr<AIActor>)>& postSpawnUpdate) {
    for (int i = 0, position = 0; i < count;
         ++i, position = i % static_cast<int>(spawnPositions.size())) {
        SpawnActorAt(actorParameters, spawnPositions[position],
                     postSpawnUpdate);
    }
}
void AIActorSpawnManager::SpawnRandomly(
    const AIActor::Parameters& actorParameters,
    const std::vector<MaxrEngine::Vector2Df>& spawnPositions, const int count,
    const std::function<void(std::shared_ptr<AIActor>)>& postSpawnUpdate,
    const int randSeed) {
    if (randSeed == -1) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
    } else {
        std::srand(randSeed);
    }
    for (int i = 0; i < count; ++i) {
        SpawnActorAt(actorParameters,
                     spawnPositions[std::rand() % spawnPositions.size()],
                     postSpawnUpdate);
    }
}
std::shared_ptr<AIActor> AIActorSpawnManager::SpawnActorAt(
    const AIActor::Parameters& actorParameters,
    const MaxrEngine::Vector2Df& position,
    const std::function<void(std::shared_ptr<AIActor>)>& postSpawnUpdate) {
    auto actor =
        std::shared_ptr<AIActor>(new AIActor(actorParameters, position));
    if (postSpawnUpdate) {
        postSpawnUpdate(actor);
    }
    auto* healthComponent =
        actor->GetGameObject()->GetComponent<HealthComponent>();
    healthComponent->AddObserver(shared_from_this());
    ++aIActorsCount;
    return actor;
}
void AIActorSpawnManager::Notify(
    std::shared_ptr<MaxrEngine::IObservable> observable) {}
}  // namespace Roguelike
