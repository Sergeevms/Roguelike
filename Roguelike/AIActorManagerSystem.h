#pragma once
#include <functional>
#include <map>
#include <memory>
#include <vector>

#include "AIActor.h"
#include "Component.h"
#include "GameObject.h"
#include "IDelayedAction.h"
#include "IFixedUpdateSystem.h"
#include "IObserver.h"
#include "Rect.h"
#include "Vector.h"

namespace Roguelike {
/**
 * @brief default fixed update time for AIActorManagerSystem
 */
constexpr float AIActorManagerSystemUpdateTime = 4.0F;
/**
 * @brief System that controlls AIActor spawn, death, position in labyrinth.
 * @details Provides functions to create AIActor instances with various spawn
 * patterns. Controls count of AIActor spawned and alive. Removes AIActor from
 * GameWorld that are not alive for a Settings::timeToRemoveAfterDeath. Checks
 * that spawned AIActor doesn't move from labyrinth area, returns them to spawn
 * point if is.
 * @see Settings
 */
class AIActorManagerSystem : public MaxrEngine::IFixedUpdateSystem,
                             public MaxrEngine::IObserver {
   public:
    /**
     * @brief Component that destroys GameObject if it isn't Alive for
     * Settings::timeToRemoveAfterDeath
     */
    class DelayedDeadAIActorDestroyer : public MaxrEngine::Component,
                                        public IDelayedAction {
       public:
        explicit DelayedDeadAIActorDestroyer(
            MaxrEngine::GameObject* gameObject);
        /**
         * @brief Updates timer throw UpdateTimer(float)
         * @param deltaTime
         */
        void Update(float deltaTime) override;
        void Render() override {};

       protected:
        /**
         * @brief Remove gameObject if is stiil dead.
         */
        void FinalAction() override;
        /**
         * @brief Check if object is still dead. If not, removes self
         * @param deltaTime
         */
        void UpdateAction(float deltaTime) override;
    };
    /**
     * @brief Get instance of AIActorManagerSystem*/
    static std::shared_ptr<AIActorManagerSystem> Instance();
    /**
     * @brief Check on spawned AIIActors for their positions and Alive status*/
    void Update() override;
    /**
     * @brief Spawn AIActors sequentially using positions from spawnPositions.
     * @details Spawn AIActors sequentially using positions from spawnPositions.
     * If AIActor was already spawned at this point, moves new AIActor spawn
     * point on offset based on size of AIActor and number of AIActors alredy
     * spawned at this point.
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
     * @brief Spawn AIActors at random positions from spawnPositions.
     * @details Spawn AIActors at random positions from spawnPositions. If
     * AIActor was already spawned at this point, moves new AIActor spawn point
     * on offset based on size of AIActor and number of AIActors alredy spawned
     * at this point.
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
    /**
     * @brief playing area rect defining it is not setted.*/
    // static const MaxrEngine::FloatRect lanyrinthRect = {-1, -1, -1, -1};

    AIActorManagerSystem() {
        fixedUpdateTime = AIActorManagerSystemUpdateTime;
    };
    ~AIActorManagerSystem() {};

    AIActorManagerSystem(AIActorManagerSystem const&) = delete;
    AIActorManagerSystem& operator=(AIActorManagerSystem const&) = delete;
    /**
     * @brief container to store spawned AIActors and their spawn points
     */
    std::map<std::weak_ptr<MaxrEngine::GameObject>, MaxrEngine::Vector2Df,
             std::owner_less<std::weak_ptr<MaxrEngine::GameObject>>>
        aIActors;
    /**
     * @brief Rectanle stores ared where AIactors should be. Doesn't perform
     * Update check is setted with {
     */
    MaxrEngine::FloatRect gameArea = {-1, -1, -1, -1};

    int aIActorsCount = 0;
};
}  // namespace Roguelike
