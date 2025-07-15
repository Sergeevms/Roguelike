#pragma once
#include "Component.h"
#include "IObserver.h"
namespace Roguelike {
class HealthComponent : public MaxrEngine::Component,
                        public MaxrEngine::IObservable {
   public:
    HealthComponent(MaxrEngine::GameObject* gameObject,
                    const float maxHealth = 0.f);

    virtual void Update(float deltaTime) override;
    virtual void Render() override;

    // Set maxHealth to newMaxHealth
    virtual void SetMaxHealth(const float newMaxHealth);
    float GetMaxHealth() const;

    void SetCurrentHealth(const float newCurrentHealth);
    float GetCurrentHealth() const;
    // Decrease health and return overdamage
    virtual float DecreaseHealth(const float damageAmount);
    // Increase health and return overheal
    virtual float IncreaseHealth(const float healingAmount);
    bool IsAlive() const;

   protected:
    float maxHealth;
    float currentHealth;
};
}  // namespace Roguelike
