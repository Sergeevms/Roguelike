#pragma once
#ifdef ROGUELIKE_DEVELOPER_LEVEL

#include "LabyrinthBuilder.h"
#include "Scene.h"

namespace Roguelike {
class DevelopLevel : public MaxrEngine::Scene {
   public:
    void Start() override;
    void Restart() override;
    virtual void Stop() override;
};
}  // namespace Roguelike
#endif  // ROGUELIKE_DEVELOPER_LEVEL