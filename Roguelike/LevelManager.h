#pragma once
#include <memory>
#include <vector>

#include "Actor.h"
#include "GameLevel.h"
#include "IObserver.h"
#include "Trigger.h"
namespace Roguelike {
class LevelManager : public MaxrEngine::IObserver {
   public:
    static std::shared_ptr<LevelManager> Instance();

    void LoadNextLevel();
    void CheckConditions();

    void Notify(std::shared_ptr<MaxrEngine::IObservable> observable) override;

    void RegisterLevel(std::unique_ptr<GameLevel>&& newLevel);
    void CheckExited(MaxrEngine::Trigger trigger, bool onEnter);

   private:
    void GenerateLevel();
    bool isAtExit = false;
    std::vector<std::unique_ptr<GameLevel>> gameLevels;
    int nextLevelNum = 0;
    LevelManager() = default;
    ~LevelManager() = default;
    LevelManager(const LevelManager&) = delete;
    LevelManager operator=(const LevelManager&) = delete;
    std::shared_ptr<ActorSave> playerData;
};
}  // namespace Roguelike
