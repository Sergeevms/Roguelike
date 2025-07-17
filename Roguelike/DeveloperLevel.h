#pragma once
#include <memory>

#include "BackgroundMusic.h"
#include "Enemy.h"
#include "Labyrinth.h"
#include "Player.h"
#include "Scene.h"

namespace Roguelike {
class DeveloperLevel : public MaxrEngine::Scene {
   public:
    void Start() override;
    void Restart() override;
    void Stop() override;

   private:
    std::shared_ptr<Player> player;
    std::shared_ptr<Enemy> enemy;
    std::shared_ptr<BackgroundMusic> backgroundMusic;
    std::shared_ptr<Labyrinth> labyrinth;
};

}  // namespace Roguelike
