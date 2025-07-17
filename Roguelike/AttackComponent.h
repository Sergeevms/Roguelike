#pragma once
#include <memory>

#include "Component.h"

namespace Roguelike {
class AttackComponent : public MaxrEngine::Component {
   public:
    explicit AttackComponent(MaxrEngine::GameObject* gameObject,
                             float cooldown = 0.0F, float damage = 0.0F,
                             float range = 0.0F,
                             std::weak_ptr<MaxrEngine::GameObject> target =
                                 std::weak_ptr<MaxrEngine::GameObject>());

    void Update(float deltaTime) override;
    void Render() override;

    virtual void Attack();

    void SetCooldown(const float newCoolDown);
    float GetCooldwon() const;

    void SetDamage(const float newDamage);
    float GetDamage() const;

    void SetRange(const float newRange);
    float GetRange() const;

    void SetTarget(std::weak_ptr<MaxrEngine::GameObject> newTarget);
    std::shared_ptr<MaxrEngine::GameObject> GetTarget() const;

   protected:
    std::weak_ptr<MaxrEngine::GameObject> target;
    float currentCooldown;
    float cooldown;
    float damage;
    float range;
};
}  // namespace Roguelike
