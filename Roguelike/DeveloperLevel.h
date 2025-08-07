#pragma once
#include "Scene.h"

namespace Roguelike {
class DeveloperLevel : public MaxrEngine::Scene {
   public:
    void Start() override;
    void Restart() override;
    void Stop() override;
};
}  // namespace Roguelike
