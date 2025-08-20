#pragma once
#include <memory>

#include "GameObject.h"
#include "IObserver.h"
#include "PerceptionComponent.h"

namespace Roguelike {
class AIPerceptionComponent : public PerceptionComponent,
                              public MaxrEngine::IObserver {
   public:
    explicit AIPerceptionComponent(
        MaxrEngine::GameObject* gameObject,
        const PerceptionComponent::Parameters& parameters = defaultParameters);
    void Notify(std::shared_ptr<IObservable> observable) override;
};
}  // namespace Roguelike
