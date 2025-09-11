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
 * @brief System that controlls AIActor spawn, death, position in labyrinthPtr.
 * @details Provides functions to create AIActor instances with various spawn
 * patterns. Spawn point provided clamped to setted gameArea. Controls count of
 * AIActor spawned and alive. Removes AIActor from GameWorld that are not alive
 * for a Settings::timeToRemoveAfterDeath. Checks that spawned AIActor doesn't
 * move from gameArea, returns them to spawn point if is.
 * @warning Need to set gameArea by Reset before spawning AIActors
 * @see Settings
 */
class AIActorManagerSystem : public MaxrEngine::IFixedUpdateSystem,
                             public MaxrEngine::IObserver {
   public:
    /**
     * @brief Component that destroys GameObject if it isn't Alive for
     * Settings::timeToRemoveAfterDeath
     */
    class DelayedDeadAIActorDestroyerComponent
        : public MaxrEngine::Component,
          public IDelayedAction,
          public MaxrEngine::IObservable {
       public:
        explicit DelayedDeadAIActorDestroyerComponent(
            MaxrEngine::GameObject* gameObject);
        /**
         * @brief Updates timer throw UpdateTimer(float)
         * @param deltaTime - time passes since last Update
         */
        void Update(float deltaTime) override;

       protected:
        /**
         * @brief Remove gameObject if is stiil dead.
         */
        void FinalAction() override;
        /**
         * @brief Check if object is still dead. If not, removes self
         * @param deltaTime - time passes since last Update
         */
        void UpdateAction(float deltaTime) override;
    };
    /**
     * @brief Get instance of AIActorManagerSystem*/
    static std::shared_ptr<AIActorManagerSystem> Instance();
    /**
     * @brief Check on spawned AIIActors for their positions. If Actor position
     * is out of gameArea, returns Actor to spawn point.*/
    void Update() override;
    /**
     * @brief Spawn AIActors sequentially using positions from spawnPositions.
     * @details Spawn AIActors sequentially using positions from spawnPositions.
     * If AIActor was already spawned at this point, moves new AIActor spawn
     * point on offset based on size of AIActor and number of AIActors alredy
     * spawned at this point.
     * @param actorParameters - Constructor parameters for AIActor.
     * @param spawnPositions - Valid spawn positions (cycled if count >
     * positions.size()). Clamped to fit gameArea when spawn.
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
     * @param spawnPositions - Valid spawn positions. Clamped to fit gameArea
     * when spawn.
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
     * @param position - Spawn position.  Clamped to fit gameArea when spawn.
     * @param postSpawnUpdate - Optional callback applied after construction
     * @return - Returns created AIActor
     */
    std::shared_ptr<AIActor> SpawnActorAt(
        const AIActor::Parameters& actorParameters,
        const MaxrEngine::Vector2Df& position,
        const std::function<void(std::shared_ptr<AIActor>)>& postSpawnUpdate =
            nullptr);
    /**
     * @brief Get notification from AIActor HealthComponent, starts destruction
     * if dead.
     * @param observable - Pointer to previously spawned AIActor.
     * HealthComponent.
     */
    void Notify(std::shared_ptr<MaxrEngine::IObservable> observable) override;
    /**
     * @brief Clear information about spawned actors, set gameArea.
     * @param newGameArea - Area where actors can be.
     */
    void Reset(const MaxrEngine::FloatRect& newGameArea);
    /**
     * @brief Gets the current count of AIActors
     * @return - Number of remaining AIActors
     */
    int GetAiActorsCount() const;

   private:
    AIActorManagerSystem() {
        fixedUpdateTime = AIActorManagerSystemUpdateTime;
    };
    ~AIActorManagerSystem() {};

    AIActorManagerSystem(AIActorManagerSystem const&) = delete;
    AIActorManagerSystem& operator=(AIActorManagerSystem const&) = delete;
    /**
     * @brief Container to store spawned AIActors and their spawn points.
     */
    std::map<std::weak_ptr<MaxrEngine::GameObject>, MaxrEngine::Vector2Df,
             std::owner_less<std::weak_ptr<MaxrEngine::GameObject>>>
        aIActors;
    /**
     * @brief Rectangle area where AIActors should be.
     */
    MaxrEngine::FloatRect gameArea = {-1, -1, -1, -1};

    int aIActorsCount = 0;
};
}  // namespace Roguelike
