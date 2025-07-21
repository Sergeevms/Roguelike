#pragma once
#include <memory>

#include "Component.h"
#include "GameObject.h"

namespace Roguelike {
class AttackComponent : public MaxrEngine::Component {
   public:
    struct AtackComponentParameters {
        float cooldown;
        float damage;
        float range;
    };
    explicit AttackComponent(
        MaxrEngine::GameObject* gameObject,
        const AtackComponentParameters& atackParameters = defaultParameters,
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
    static const AtackComponentParameters defaultParameters;
    std::weak_ptr<MaxrEngine::GameObject> target;
    float currentCooldown;
    float cooldown;
    float damage;
    float range;
};
}  // namespace Roguelike
