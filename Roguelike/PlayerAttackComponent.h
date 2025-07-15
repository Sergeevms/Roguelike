#pragma once
#include "AttackComponent.h"
#include "IObserver.h"
namespace Roguelike {
class PlayerAttackComponent : public AttackComponent,
                              public MaxrEngine::IObserver {
   public:
    PlayerAttackComponent(MaxrEngine::GameObject* gameObject,
                          float cooldown = 0.f, float damage = 0.f,
                          float range = 0.f,
                          std::weak_ptr<MaxrEngine::GameObject> target =
                              std::weak_ptr<MaxrEngine::GameObject>());
    virtual void Notify(
        std::shared_ptr<MaxrEngine::IObservable> observable) override;
};
}  // namespace Roguelike
