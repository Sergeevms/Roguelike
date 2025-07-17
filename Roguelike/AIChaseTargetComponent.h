#pragma once
#include "Component.h"
namespace Roguelike {
class AIChaseTargetComponent : public MaxrEngine::Component {
   public:
    explicit AIChaseTargetComponent(MaxrEngine::GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

    void SetMaximumChaseRadius(float newMaximumRadius);
    void SetMinimumChaseRadius(float newMinimuRadius);

   private:
    float minumumChaseRadius = 0.0F;
    float maximumChaseRadius = 0.0F;
};
}  // namespace Roguelike
