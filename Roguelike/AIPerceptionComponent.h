#pragma once
#include <memory>
#include <string_view>
#include <vector>

#include "GameObject.h"
#include "IObserver.h"
#include "PerceptionComponent.h"

namespace Roguelike {
class AIPerceptionComponent : public PerceptionComponent,
                              public MaxrEngine::IObserver {
   public:
    static constexpr std::string_view isActorsDetectedBBName =
        "Perception_ActorsDetected";
    static constexpr std::string_view detectedActorsBBName =
        "Perception_DetectedActors";
    explicit AIPerceptionComponent(
        MaxrEngine::GameObject* gameObject,
        const PerceptionComponent::Parameters& parameters = defaultParameters);
    void UpdateDetectedActors(
        const std::vector<MaxrEngine::GameObject*>& actors) override;
    void Notify(std::shared_ptr<IObservable> observable) override;
};
}  // namespace Roguelike
