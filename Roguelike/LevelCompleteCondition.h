#pragma once
#include <memory>
#include <string>

#include "Trigger.h"

namespace Roguelike {
class GameLevel;

/**
 * @brief Base class for level completion conditions
 * @details Defines the interface for conditions that must be met to complete a
 * level
 */
class LevelCompleteCondition {
   public:
    /**
     * @brief Enumeration of possible level completion condition types
     */
    enum class Type { ExitReached, AllEnemyKilled };

    /**
     * @brief Creates a condition instance of the specified type
     * @param gameLevel The game level to check conditions against
     * @param type The type of condition to create
     * @return Shared pointer to the created condition
     */
    static std::shared_ptr<LevelCompleteCondition> CreateCondition(
        const std::shared_ptr<GameLevel> gameLevel, const Type type);

    /**
     * @brief Constructs a level completion condition
     * @param gameLevel The game level to check conditions against
     * @param conditionDescription Text description of the condition
     */
    LevelCompleteCondition(const std::shared_ptr<GameLevel> gameLevel,
                           const std::string& conditionDescription);
    /**
     * @brief Checks if the condition has been completed
     * @return True if the condition is met, false otherwise
     */
    virtual bool Completed() const = 0;
    /**
     * @brief Post-constructor initialization for the condition
     */
    virtual void Init();
    /**
     * @brief Gets the description of the condition
     * @return Reference to the condition description string
     */
    const std::string& GetDescription() const;

   protected:
    std::weak_ptr<GameLevel> gameLevel;  ///< Weak reference to the game level
    std::string conditionDescription;    ///< Text description of the condition
};

/**
 * @brief Condition for completing level by reaching the exit
 */
class ExitReached : public LevelCompleteCondition {
   public:
    /**
     * @brief Constructs an exit reached condition
     * @param gameLevel The game level to check
     * @param conditionDescription Description of the condition
     */
    explicit ExitReached(
        std::shared_ptr<GameLevel> gameLevel,
        const std::string& conditionDescription = "Reach level exit");
    /**
     * @brief Checks if the player has entered or exited the level exit
     * @details Designed to be called by exit trigger. Checks that player
     * entered/exited trigger, updates reached status accordingly
     * @param trigger The collision trigger information
     * @param onEnter True if entering, false if exiting
     */
    void CheckExited(MaxrEngine::Trigger trigger, bool onEnter);
    /**
     * @brief Checks if the exit has been reached
     * @return True if the exit has been reached, false otherwise
     */
    bool Completed() const override;

   private:
    bool reached = false;  ///< Flag indicating if the exit has been reached
};

/**
 * @brief Condition for completing level by killing all enemies
 */
class EnemyKilled : public LevelCompleteCondition {
   public:
    /**
     * @brief Constructs enemy killed condition
     * @param gameLevel The game level to monitor
     * @param conditionDescription Description text for the condition
     */
    explicit EnemyKilled(
        std::shared_ptr<GameLevel> gameLevel,
        const std::string& conditionDescription = "Kill all enemies");
    /**
     * @brief Checks if all enemies have been killed
     * @details Checks information based on AIActorManagerSystem data on alive
     * AIActors
     * @return True if all enemies dead, false otherwise
     */
    bool Completed() const override;
};
}  // namespace Roguelike
