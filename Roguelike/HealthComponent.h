#pragma once
#include <memory>

#include "Component.h"
#include "IObserver.h"
#include "ISaveable.h"
namespace Roguelike {
/**
 * @brief Class for saving HealthComponent state.
 * @see HealthComponent
 */
class HealthSave {
    friend class HealthComponent;
    float maxHealth;
    float currentHealth;
};
class HealthComponent : public MaxrEngine::Component,
                        public MaxrEngine::IObservable,
                        public ISaveable<HealthComponent, HealthSave> {
   public:
    explicit HealthComponent(MaxrEngine::GameObject* gameObject,
                             const float maxHealth = 0.0F);

    void Update(float deltaTime) override;

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
    void SaveImpl(std::shared_ptr<HealthSave> save) const;
    void LoadImpl(std::shared_ptr<const HealthSave> save);

   protected:
    float maxHealth;
    float currentHealth;

   private:
    friend class ISaveable<HealthComponent, HealthSave>;
};
}  // namespace Roguelike
