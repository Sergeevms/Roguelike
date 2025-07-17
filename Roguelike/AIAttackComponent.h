#pragma once
#include <memory>

#include "AttackComponent.h"
#include "GameObject.h"
namespace Roguelike {
class AIAttackComponent : public AttackComponent {
   public:
    explicit AIAttackComponent(MaxrEngine::GameObject* gameObject,
                               float cooldown = 0.0F, float damage = 0.0F,
                               float range = 0.0F,
                               std::weak_ptr<MaxrEngine::GameObject> target =
                                   std::weak_ptr<MaxrEngine::GameObject>());
    void Update(float deltaTime) override;
};
}  // namespace Roguelike
