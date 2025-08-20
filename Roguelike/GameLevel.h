#pragma once
#include <memory>

#include "Labyrinth.h"
#include "LabyrinthBuilder.h"
#include "PlayerActor.h"
#include "Scene.h"
namespace Roguelike {
class GameLevel : public MaxrEngine::Scene {
   public:
    struct Parameters {
        LabyrinthBuilder::Parameters builderParameters;
        int enemyCount;
    };

    GameLevel(const Parameters& parameters);

    void Start() override;
    void Restart() override;
    void Stop() override;

    std::shared_ptr<PlayerActor> GetPlayer();
    std::shared_ptr<Labyrinth> GetLabyrinth();

   private:
    Parameters parameters;
    std::shared_ptr<PlayerActor> player;
    std::shared_ptr<Labyrinth> labyrinth;
};
}  // namespace Roguelike
