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
#include "TransformComponent.h"
#include "Utility.h"
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
    for (auto actorIterator = aIActors.begin();
         actorIterator != aIActors.end();) {
        // Check that AIActor not destroyed yet
        if (actorIterator->first.expired()) {
            // Remove from map if is destroyed
            actorIterator = aIActors.erase(actorIterator);
        } else {
            // Check AIActor position
            auto actor = actorIterator->first.lock();
            auto* transform =
                actor->GetComponent<MaxrEngine::TransformComponent>();
            if (!InRect(gameArea.topLeft, gameArea.GetSize(),
                        transform->GetWorldPosition())) {
                // Move actor to spawn point if is out of gameAreaS
                transform->SetWorldPosition(actorIterator->second);
            }
            ++actorIterator;
        }
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
    // Create new actor and aplly postSpawnUpdate if setted
    auto actor =
        std::shared_ptr<AIActor>(new AIActor(actorParameters, position));
    if (postSpawnUpdate) {
        postSpawnUpdate(actor);
    }
    // Add self to HealthComponent Observers list
    auto* healthComponent =
        actor->GetGameObject()->GetComponent<HealthComponent>();
    healthComponent->AddObserver(Instance());

    ++aIActorsCount;
    aIActors[actor->GetGameObject()->weak_from_this()] = position;
    return actor;
}
void AIActorManagerSystem::Notify(
    std::shared_ptr<MaxrEngine::IObservable> observable) {
    // Identify observable as AIActor HealthComponent
    auto healthComponent =
        std::dynamic_pointer_cast<HealthComponent>(observable);
    if (healthComponent) {
        if (healthComponent && !healthComponent->IsAlive()) {
            // If AIActor is dead, add DelayedDeadAIActorDestroyerComponent to
            // destroy AIActor
            auto delayedDestroyer =
                healthComponent->GetGameObject()
                    ->AddComponent<DelayedDeadAIActorDestroyerComponent>();
            delayedDestroyer->StartTimer(
                Settings::Instance()->timeToRemoveAfterDeath);
            delayedDestroyer->AddObserver(Instance());
        }
        return;
    }
    // Identify observable as AIActor DelayedDeadAIActorDestroyerComponent,
    // reduce count of actors if is
    auto destroyer = std::dynamic_pointer_cast<
        AIActorManagerSystem::DelayedDeadAIActorDestroyerComponent>(observable);
    if (destroyer) {
        --aIActorsCount;
    }
}
void AIActorManagerSystem::Reset(const MaxrEngine::FloatRect& newGameArea) {
    aIActors.clear();
    gameArea = newGameArea;
}
AIActorManagerSystem::DelayedDeadAIActorDestroyerComponent::
    DelayedDeadAIActorDestroyerComponent(MaxrEngine::GameObject* gameObject)
    : Component(gameObject) {}
void AIActorManagerSystem::DelayedDeadAIActorDestroyerComponent::Update(
    float deltaTime) {
    UpdateTimer(deltaTime);
}
void AIActorManagerSystem::DelayedDeadAIActorDestroyerComponent::FinalAction() {
    if (auto* healthComponent = gameObject->GetComponent<HealthComponent>()) {
        if (healthComponent->IsAlive()) {
            // Remove component if AIActor became Alive
            gameObject->RemoveComponent(this);
        } else {
            // Notify AIACtorManagerSystem about destroying AIActor
            Emit();
            // Remove gameObject from GameWorld
            MaxrEngine::GameWorld::Instance()->DestroyGameObject(gameObject);
        }
    }
}
// NOLINTBEGIN(misc-unused-parameters) : overrided method with parameter
void AIActorManagerSystem::DelayedDeadAIActorDestroyerComponent::UpdateAction(
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
