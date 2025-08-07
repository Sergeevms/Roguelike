#pragma once
#include "Component.h"
#include "IObserver.h"
namespace Roguelike {
class ArmorComponent : public MaxrEngine::Component,
                       public MaxrEngine::IObservable {
   public:
    struct Parameters {
        float maxArmorPoints;
        float damageReduction;
    };
    static const Parameters defaultParameters;
    explicit ArmorComponent(
        MaxrEngine::GameObject* gameObject,
        const ArmorComponent::Parameters& parameters = defaultParameters);

    void Update(float deltaTime) override;
    void Render() override;

    void SetMaxArmorPoints(const float newMaxArmorPoints);
    float GetMaxArmorPoints() const;

    /** Sets damage reduction in 0.0F - 1.0F range
     1.0F for absorbing 100% at each damage applies, 0.1F for absorbing 10% of
     damage applied and 90% moving throw armor
     */
    void SetDamageReduction(const float newDamageReduction);
    float GetDamageReduction() const;

    void SetCurrentArmorPoints(const float newCurrentArmorPoints);
    float GetCurrentArmorPoints() const;
    /// Return damage gone throw armor
    virtual float ApplyDamage(const float damageAmount);
    /// Increase armorPoints
    virtual float IncreaseArmorPoints(const float armorPointAmount);
    bool IsNotBroken() const;

   protected:
    float maxArmorPoints;
    float currentArmorPoints;
    float damageReduction;
};
}  // namespace Roguelike
