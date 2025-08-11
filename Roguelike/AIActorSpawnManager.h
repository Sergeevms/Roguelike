#pragma once
#include <functional>
#include <memory>
#include <vector>

#include "AIActor.h"
#include "IDelayedAction.h"
#include "IObserver.h"
#include "Vector.h"

namespace Roguelike {
/**
 * @brief Spawner functions for AI-controlled actors
 * @details Provides functions to create AIActor instances with various spawn
 * patterns. Controls count of AIActor spawned and alive. Removes AIActor from
 * GameWorld that are not alive for a Settings::timeToRemoveAfterDeath
 * @see Settings
 */
class AIActorSpawnManager
    : public MaxrEngine::IObserver,
      public std::enable_shared_from_this<AIActorSpawnManager> {
   public:
    /**
     * @brief Spawn AIActors sequentially using positions from spawnPositions.
     * @param actorParameters - Constructor parameters for AIActor.
     * @param spawnPositions - Valid spawn positions (cycled if count >
     * positions.size())
     * @param count - Number of AIActors to spawn
     * @param postSpawnUpdate - Optional callback applied to each spawned actor
     */
    void Spawn(const AIActor::Parameters& actorParameters,
               const std::vector<MaxrEngine::Vector2Df>& spawnPositions,
               const int count,
               const std::function<void(std::shared_ptr<AIActor>)>&
                   postSpawnUpdate = nullptr);
    /**
     * @brief Spawn AIActors at random positions from spawnPositions
     * @param actorParameters - Constructor parameters for AIActor
     * @param spawnPositions - Valid spawn positions
     * @param count - Number of AIActors to spawn
     * @param randSeed - Seed for RNG (-1 = time-based seed)
     * @param postSpawnUpdate - Optional callback applied to each spawned actor
     */
    void SpawnRandomly(const AIActor::Parameters& actorParameters,
                       const std::vector<MaxrEngine::Vector2Df>& spawnPositions,
                       const int count,
                       const std::function<void(std::shared_ptr<AIActor>)>&
                           postSpawnUpdate = nullptr,
                       const int randSeed = -1);
    /**
     * @brief Spawn a single AIActor at specified position
     * @param actorParameters - Constructor parameters for AIActor
     * @param position - Spawn position
     * @param postSpawnUpdate - Optional callback applied after construction
     * @return returns created AIActor
     */
    std::shared_ptr<AIActor> SpawnActorAt(
        const AIActor::Parameters& actorParameters,
        const MaxrEngine::Vector2Df& position,
        const std::function<void(std::shared_ptr<AIActor>)>& postSpawnUpdate =
            nullptr);
    /**
     * @brief Get notification from AIActor HealthComponent, starts destruction
     * if dead.
     * @param observable - pointer to previously spawned AIActor
     * HealthComponent.
     */
    void Notify(std::shared_ptr<MaxrEngine::IObservable> observable) override;

   private:
    int aIActorsCount = 0;
};
class DelayedAIActorDestroyer : public IDelayedAction {};
}  // namespace Roguelike
