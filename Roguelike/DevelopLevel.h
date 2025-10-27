#pragma once
#ifdef ROGUELIKE_DEVELOPER_LEVEL

#include "Labyrinth.h"
#include "Scene.h"

namespace Roguelike {
class DevelopLevel : public MaxrEngine::Scene {
   public:
    void Start() override;
    void Restart() override;
    virtual void Stop() override;

   private:
    std::shared_ptr<Labyrinth> labyrinth;
};
}  // namespace Roguelike
#endif  // ROGUELIKE_DEVELOPER_LEVEL