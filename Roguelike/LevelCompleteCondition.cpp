#include "LevelCompleteCondition.h"

#include <memory>
#include <string>

#include "AIActorManagerSystem.h"
#include "ColliderComponent.h"
#include "GameLevel.h"
#include "Trigger.h"
namespace Roguelike {
std::shared_ptr<LevelCompleteCondition> LevelCompleteCondition::CreateCondition(
    const std::shared_ptr<GameLevel> gameLevel, const Type type) {
    switch (type) {
        case Type::ExitReached:
            return std::make_shared<ExitReached>(gameLevel);
        case Type::AllEnemyKilled:
            return std::make_shared<EnemyKilled>(gameLevel);
        default:
            return nullptr;
    }
}
Roguelike::LevelCompleteCondition::LevelCompleteCondition(
    const std::shared_ptr<GameLevel> gameLevel,
    const std::string& conditionDescription)
    : gameLevel(gameLevel), conditionDescription(conditionDescription) {};
void LevelCompleteCondition::Init() {}
const std::string& LevelCompleteCondition::GetDescription() const {
    return conditionDescription;
};

ExitReached::ExitReached(std::shared_ptr<GameLevel> gameLevel,
                         const std::string& conditionDescription)
    : LevelCompleteCondition(gameLevel, conditionDescription) {};
void ExitReached::CheckExited(MaxrEngine::Trigger trigger, bool onEnter) {
    if (auto level = gameLevel.lock()) {
        const auto* playerObject = level->GetPlayer()->GetGameObject();
        const auto* firstObject = trigger.first->GetGameObject();
        const auto* secondObject = trigger.second->GetGameObject();
        if (playerObject == firstObject || playerObject == secondObject) {
            reached = onEnter;
        }
    }
}
bool ExitReached::Completed() const { return reached; }

EnemyKilled::EnemyKilled(std::shared_ptr<GameLevel> gameLevel,
                         const std::string& conditionDescription)
    : LevelCompleteCondition(gameLevel, conditionDescription) {}
bool EnemyKilled::Completed() const {
    return AIActorManagerSystem::Instance()->GetAiActorsCount() <= 0;
}
}  // namespace Roguelike