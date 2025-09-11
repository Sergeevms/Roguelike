#pragma once
#include <memory>
#include <vector>

#include "Labyrinth.h"
#include "LabyrinthBuilder.h"
#include "LevelCompleteCondition.h"
#include "PlayerActor.h"
#include "Scene.h"
namespace Roguelike {
/**
 * @brief Represents a game level containing a labyrinthPtr, player, and enemies
 * @details Manages the lifecycle of a game level including starting,
 * restarting, and stopping the level. Provides access to the level's player and
 * labyrinthPtr.
 */
class GameLevel : public MaxrEngine::Scene {
   public:
    /**
     * @brief Parameters used to configure a game level
     */
    struct Parameters {
        LabyrinthBuilder::Parameters
            builderParameters;  ///< Parameters for labyrinthPtr generation
        std::vector<LevelCompleteCondition::Type>
            completeConditions;  ///< Conditions to complete the level
        int enemyCount;          ///< Number of enemies to spawn in the level
    };

    /**
     * @brief Constructs a GameLevel with the specified parameters
     * @param parameters Configuration parameters for the level
     */
    explicit GameLevel(const Parameters& parameters);

    /**
     * @brief Starts the game level
     * @details Generates the labyrinthPtr, spawns enemies, and places the
     * player
     */
    void Start() override;
    /**
     * @brief Restarts the game level
     * @details Stops the current level and then starts with the same parameters
     */
    void Restart() override;
    /**
     * @brief Stops the game level
     * @details Cleans up all level resources and clears the game world
     */
    void Stop() override;

    /**
     * @brief Gets the player actor instance
     * @return Shared pointer to the player actor
     */
    std::shared_ptr<PlayerActor> GetPlayer();
    /**
     * @brief Gets the labyrinthPtr instance
     * @return Shared pointer to the labyrinthPtr
     */
    std::shared_ptr<Labyrinth> GetLabyrinth();

   private:
    Parameters parameters;  ///< Configuration parameters for the level
    std::shared_ptr<PlayerActor> player;   ///< The player actor instance
    std::shared_ptr<Labyrinth> labyrinth;  ///< The labyrinthPtr instance
};
}  // namespace Roguelike
