#pragma once
#include <memory>

#include "Component.h"
#include "GameObject.h"

namespace Roguelike {
/** Base Attack component
 * Manages attack startupTime, cooldown, damage, range and target.
 * Damage flows throw target's Block, Armor and Health component
 * Can't start attack if bloking. Using Block after attack started will interupt
 * it.
 */
class AttackComponent : public MaxrEngine::Component {
   public:
    /** Struct storing AttackComponent parameters*/
    struct Parameters {
        /** Time between initiating attack and dealing damage*/
        float startupTime;
        /** Time before next attack can start*/
        float cooldown;
        /** Base damage*/
        float damage;
        /** Maximum distance to target for attack to be effective*/
        float range;
    };
    explicit AttackComponent(
        MaxrEngine::GameObject* gameObject,
        const Parameters& atackParameters = defaultParameters,
        std::weak_ptr<MaxrEngine::GameObject> target =
            std::weak_ptr<MaxrEngine::GameObject>());
    /** Updates currentCooldown time, checks if startupTime ended*/
    void Update(float deltaTime) override;
    void Render() override;
    /** Starting attack - initiate Cooldown */
    virtual void StartAttack();
    /** Process dealing damage to target*/
    virtual void ProcessAtack();
    /** Sets startupTime*/
    void SetStartupTime(const float newStartupTime);
    /** Get current startupTime*/
    float GetStartupTime() const;
    /** Get time left before dealing damage*/
    float GetTimeTillAttack() const;
    /** Sets cooldDown time*/
    void SetCooldown(const float newCoolDown);
    /** Get current coolDown*/
    float GetCooldwon() const;
    /** Get time before next attack can be started*/
    float GetCurrentCooldown() const;
    /** Set attack damage*/
    void SetDamage(const float newDamage);
    /** Get current attack damage*/
    float GetDamage() const;
    /** Set attack range*/
    void SetRange(const float newRange);
    /** Get current atack range*/
    float GetRange() const;
    /** Set target for atack*/
    void SetTarget(std::weak_ptr<MaxrEngine::GameObject> newTarget);
    /** Get current target for atack*/
    std::shared_ptr<MaxrEngine::GameObject> GetTarget() const;

   protected:
    /** Default parameters used in constructor if Parameters not specified*/
    static const Parameters defaultParameters;
    std::weak_ptr<MaxrEngine::GameObject> target;
    /** Time between initiating attack and dealing damage*/
    float startupTime;
    /** Time left before damage dealing*/
    float timeTillAttack;
    /** Time left till attack available*/
    float currentCooldown;
    /** Time before next attack can start*/
    float cooldown;
    /** Base damage*/
    float damage;
    /** Maximum distance to target for attack to be effective*/
    float range;
};
}  // namespace Roguelike
