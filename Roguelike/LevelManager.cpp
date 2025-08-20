#include "LevelManager.h"

#include <memory>

#include "ColliderComponent.h"
#include "GameLevel.h"
#include "IObserver.h"
#include "Trigger.h"

namespace Roguelike {
std::shared_ptr<LevelManager> LevelManager::Instance() {
    static std::shared_ptr<LevelManager> instance(new LevelManager(),
                                                  [](LevelManager*) {});
    return instance;
}
void LevelManager::LoadNextLevel() {
    if (nextLevelNum >= gameLevels.size()) {
        GenerateLevel();
    }
    if (nextLevelNum > 0) {
        auto& currentLevel = gameLevels[nextLevelNum - 1];
        playerData = currentLevel->GetPlayer()->Save();
        currentLevel->Stop();
    }
    gameLevels[nextLevelNum]->Start();
    if (playerData) {
        gameLevels[nextLevelNum]->GetPlayer()->Load(playerData);
    }
    ++nextLevelNum;
}
void LevelManager::CheckConditions() {
    if (isAtExit) {
        LoadNextLevel();
    }
}
void LevelManager::Notify(std::shared_ptr<MaxrEngine::IObservable> observable) {
    CheckConditions();
}
void LevelManager::RegisterLevel(std::unique_ptr<GameLevel>&& newLevel) {
    gameLevels.emplace_back(std::move(newLevel));
}
void LevelManager::CheckExited(MaxrEngine::Trigger trigger, bool onEnter) {
    const auto* playerObject =
        gameLevels[nextLevelNum - 1]->GetPlayer()->GetGameObject();
    const auto* firstObject = trigger.first->GetGameObject();
    const auto* secondObject = trigger.second->GetGameObject();
    if (playerObject == firstObject || playerObject == secondObject) {
        isAtExit = onEnter;
    }
    CheckConditions();
}
void LevelManager::GenerateLevel() {}
}  // namespace Roguelike
