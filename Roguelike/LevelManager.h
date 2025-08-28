#pragma once
#include <memory>
#include <vector>

#include "Actor.h"
#include "GameLevel.h"
#include "IObserver.h"
#include "LevelCompleteCondition.h"
namespace Roguelike {
/**
 * @brief Manages game levels and progression between them
 * @details Handles level loading, completion condition checking,
 * and player progression between levels
 */
class LevelManager : public MaxrEngine::IObserver {
   public:
    /**
     * @brief Gets the singleton instance of LevelManager
     * @return Shared pointer to LevelManager instance
     */
    static std::shared_ptr<LevelManager> Instance();

    /**
     * @brief Loads the next level in sequence
     * @details Handles saving player state, generating new levels if needed,
     * and setting up completion conditions
     */
    void LoadNextLevel();

    /**
     * @brief Handles notifications from observable objects
     * @details Handles notification from InputComponent, starts condition check
     * if level transfer input is active
     * @param observable The object sending the notification
     */
    void Notify(std::shared_ptr<MaxrEngine::IObservable> observable) override;

    /**
     * @brief Registers a level with specified parameters
     * @param parameters Parameters for the level to register
     */
    void RegisterLevel(const GameLevel::Parameters& parameters);

    /**
     * @brief Gets the list of current level completion conditions
     * @return Reference to vector of completion conditions
     */
    std::vector<std::shared_ptr<LevelCompleteCondition>>&
    GetCompleteConditions();

   private:
    /**
     * @brief Generates a new level with increased difficulty
     * @details Uses the last level parameters or default settings if no levels
     * exist, then increases labyrinth size and enemy count for progressive
     * difficulty
     */
    void GenerateLevel();
    /**
     * @brief Checks if all level completion conditions are met
     * @details Loads next level if all conditions are satisfied
     */
    void CheckConditions();
    std::vector<GameLevel::Parameters>
        gameLevelParameters;  ///< Parameters for all registered levels
    std::shared_ptr<GameLevel> currentLevel;  ///< Currently active level
    int nextLevelNum = 0;                     ///< Index of next level to load
    LevelManager() = default;
    ~LevelManager() = default;
    LevelManager(const LevelManager&) = delete;
    LevelManager operator=(const LevelManager&) = delete;
    std::vector<std::shared_ptr<LevelCompleteCondition>>
        conditions;  ///< Current level completion conditions
    std::shared_ptr<ActorSave>
        playerData;  ///< Saved player data between levels
};
}  // namespace Roguelike
