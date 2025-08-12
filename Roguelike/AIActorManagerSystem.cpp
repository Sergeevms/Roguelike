#include "AIActorManagerSystem.h"

#include <cstdlib>
#include <ctime>
#include <functional>
#include <memory>
#include <vector>

#include "AIActor.h"
#include "Component.h"
#include "GameWorld.h"
#include "HealthComponent.h"
#include "IObserver.h"
#include "Settings.h"
#include "Vector.h"

namespace Roguelike {
/**
 * @brief Vector with possible directions for offsets to use when two or more
 * AIActors spawnded on one spawnPoint.
 */
static const std::vector<MaxrEngine::Vector2Df> baseOffsets = {
    {0, 0}, {0, -1}, {0, 1},  {1, 0},  {1, -1},
    {1, 1}, {-1, 0}, {-1, 1}, {-1, -1}};
std::shared_ptr<AIActorManagerSystem> AIActorManagerSystem::Instance() {
    const static std::shared_ptr<AIActorManagerSystem> instance(
        new AIActorManagerSystem(), [](AIActorManagerSystem*) {});
    return instance;
}
void AIActorManagerSystem::Update() {
    for (auto actorPair : aIActors) {
    }
}
void AIActorManagerSystem::Spawn(
    const AIActor::Parameters& actorParameters,
    const std::vector<MaxrEngine::Vector2Df>& spawnPositions, const int count,
    const std::function<void(std::shared_ptr<AIActor>)>& postSpawnUpdate) {
    // Get actorSize to use to move spawn position if actor allready was spawned
    // at it
    const MaxrEngine::Vector2Df actorSize =
        MaxrEngine::Convert<MaxrEngine::Vector2Df>(
            actorParameters.baseActorParameters.spriteSize);
    // Vector to store number of actors spawned at conrecte spawn point
    std::vector<int> actorSpawnedAt(spawnPositions.size(), 0);
    for (int i = 0, positionNumber = 0; i < count;
         ++i, positionNumber = i % static_cast<int>(spawnPositions.size())) {
        // Calculate spawn position as given spawn position plus offset choosed
        // according to alredy spawned actors;
        const MaxrEngine::Vector2Df spawnPosition =
            spawnPositions[positionNumber] +
            actorSize * baseOffsets[actorSpawnedAt[positionNumber]];
        // Spawn actor as spawnPosition
        SpawnActorAt(actorParameters, spawnPosition, postSpawnUpdate);
        // Increase number of actors spawned at current position
        ++actorSpawnedAt[positionNumber];
    }
}
void AIActorManagerSystem::SpawnRandomly(
    const AIActor::Parameters& actorParameters,
    const std::vector<MaxrEngine::Vector2Df>& spawnPositions, const int count,
    const std::function<void(std::shared_ptr<AIActor>)>& postSpawnUpdate,
    const int randSeed) {
    // Set up RNG seed according to input
    if (randSeed == -1) {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
    } else {
        std::srand(randSeed);
    }
    // Get actorSize to use to move spawn position if actor already was spawned
    // at it
    const MaxrEngine::Vector2Df actorSize =
        MaxrEngine::Convert<MaxrEngine::Vector2Df>(
            actorParameters.baseActorParameters.spriteSize);
    // Vector to store number of actors spawned at conrecte spawn point
    std::vector<int> actorSpawnedAt(spawnPositions.size(), 0);
    for (int i = 0; i < count; ++i) {
        const int positionNumber =
            std::rand() % static_cast<int>(spawnPositions.size());
        // Calculate spawn position as given spawn position plus offset choosed
        // according to allready spawned actors;
        const MaxrEngine::Vector2Df spawnPosition =
            spawnPositions[positionNumber] +
            actorSize * baseOffsets[actorSpawnedAt[positionNumber]];
        // Spawn actor as spawnPosition
        SpawnActorAt(actorParameters, spawnPosition, postSpawnUpdate);
        // Increase number of actors spawned at current position
        ++actorSpawnedAt[positionNumber];
    }
}
std::shared_ptr<AIActor> AIActorManagerSystem::SpawnActorAt(
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
    healthComponent->AddObserver(Instance());
    ++aIActorsCount;
    aIActors[actor->GetGameObject()->weak_from_this()] = position;
    return actor;
}
void AIActorManagerSystem::Notify(
    std::shared_ptr<MaxrEngine::IObservable> observable) {
    auto healthComponent =
        std::dynamic_pointer_cast<HealthComponent>(observable);
    if (!healthComponent->IsAlive()) {
        auto delayedDestroyer =
            healthComponent->GetGameObject()
                ->AddComponent<DelayedDeadAIActorDestroyer>();
        delayedDestroyer->StartTimer(
            Settings::Instance()->timeToRemoveAfterDeath);
    }
}
AIActorManagerSystem::DelayedDeadAIActorDestroyer::DelayedDeadAIActorDestroyer(
    MaxrEngine::GameObject* gameObject)
    : Component(gameObject) {}
void AIActorManagerSystem::DelayedDeadAIActorDestroyer::Update(
    float deltaTime) {
    UpdateTimer(deltaTime);
}
void AIActorManagerSystem::DelayedDeadAIActorDestroyer::FinalAction() {
    if (auto* healthComponent = gameObject->GetComponent<HealthComponent>()) {
        if (healthComponent->IsAlive()) {
            // Remove component if AIActor became Alive
            gameObject->RemoveComponent(this);
        } else {
            // Remove gameObject from GameWorld
            MaxrEngine::GameWorld::Instance()->DestroyGameObject(gameObject);
        }
    }
}
// NOLINTBEGIN(misc-unused-parameters) : overrided method with parameter
void AIActorManagerSystem::DelayedDeadAIActorDestroyer::UpdateAction(
    float deltaTime) {
    if (auto* healthComponent = gameObject->GetComponent<HealthComponent>()) {
        if (healthComponent->IsAlive()) {
            // Remove component if AIActor became Alive
            gameObject->RemoveComponent(this);
        }
    }
}
// NOLINTEND(misc-unused-parameters)
}  // namespace Roguelike
