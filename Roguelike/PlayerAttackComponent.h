#pragma once
#include <memory>

#include "AttackComponent.h"
#include "GameObject.h"
#include "IObserver.h"
namespace Roguelike {
class PlayerAttackComponent : public AttackComponent,
                              public MaxrEngine::IObserver {
   public:
    explicit PlayerAttackComponent(
        MaxrEngine::GameObject* gameObject,
        const AtackComponentParameters& atackParameters = defaultParameters,
        std::weak_ptr<MaxrEngine::GameObject> target =
            std::weak_ptr<MaxrEngine::GameObject>());
    virtual void Notify(
        std::shared_ptr<MaxrEngine::IObservable> observable) override;
};
}  // namespace Roguelike
