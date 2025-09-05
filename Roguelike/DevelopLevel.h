#pragma once
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
