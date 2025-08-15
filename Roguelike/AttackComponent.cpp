#include "AttackComponent.h"

#include <cassert>
#include <memory>

#include "ArmorComponent.h"
#include "BlockComponent.h"
#include "Component.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "Logger.h"
#include "SpriteAnimationComponent.h"

namespace Roguelike {
const AttackComponent::Parameters AttackComponent::defaultParameters = {
    .startupTime = 0.0F, .cooldown = 0.0F, .damage = 0.0F, .range = 0.0F};

AttackComponent::AttackComponent(MaxrEngine::GameObject* gameObject,
                                 const Parameters& atackParameters,
                                 std::weak_ptr<MaxrEngine::GameObject> target)
    : Component(gameObject),
      target(target),
      startupTime(atackParameters.startupTime),
      timeTillAttack(0.0F),
      currentCooldown(0.0F),
      cooldown(atackParameters.cooldown),
      damage(atackParameters.damage),
      range(atackParameters.range) {
    healtComponentPtr = gameObject->GetComponentSharedPtr<HealthComponent>();
}

void AttackComponent::Update(float deltaTime) {
    // Update coldown timer if started
    if (currentCooldown > 0.0F) {
        currentCooldown -= deltaTime;
    }
    // Update startup timer if started
    if (timeTillAttack > 0.0F) {
        // Interupt attack if is blocking
        bool interupted = false;
        if (auto* blockComponent = gameObject->GetComponent<BlockComponent>()) {
            if (blockComponent->GetIsBlocking()) {
                LOG_INFO("Attack interupted by blocking");
                if (auto* spriteAnimation =
                        gameObject->GetComponent<
                            MaxrEngine::SpriteAnimationComponent>()) {
                    spriteAnimation->StartAnimation("Idle", true);
                }
                timeTillAttack = 0.0F;
                interupted = true;
            }
        }
        if (!interupted) {
            timeTillAttack -= deltaTime;
            if (timeTillAttack <= 0.0F) {
                // Atack if startup timer ended
                ProcessAttack();
            }
        }
    }
}

void AttackComponent::StartAttack() {
    // Check that alive and not bloking now
    auto healthComponent = healtComponentPtr.lock();
    if (healthComponent && healthComponent->IsAlive()) {
        if (auto* blockComponent = gameObject->GetComponent<BlockComponent>()) {
            if (blockComponent->GetIsBlocking()) {
                LOG_INFO("Can't start attack while bloking");
                return;
            }
        }
        if (auto* spriteAnimation =
                gameObject
                    ->GetComponent<MaxrEngine::SpriteAnimationComponent>()) {
            spriteAnimation->StartAnimation("Attack windup");
        }
        currentCooldown = cooldown;
        timeTillAttack = startupTime;
    }
}

void AttackComponent::ProcessAttack() {
    auto healthComponent = healtComponentPtr.lock();
    if (healthComponent && healthComponent->IsAlive()) {
        if (auto* spriteAnimation =
                gameObject
                    ->GetComponent<MaxrEngine::SpriteAnimationComponent>()) {
            spriteAnimation->StartAnimation("Attack");
        }
        auto* attacker = gameObject;
        // Check that target still exist
        if (auto targetPtr = target.lock()) {
            // Check that target is in atack range
            auto distance =
                (targetPtr->GetComponent<MaxrEngine::TransformComponent>()
                     ->GetWorldPosition() -
                 attacker->GetComponent<MaxrEngine::TransformComponent>()
                     ->GetWorldPosition())
                    .GetLength();
            if (distance > range) {
                LOG_INFO("Target is out of attack range");
                return;
            }
            auto damageLeft = damage;
            // Apply damage to BlockComponent if it exists
            if (auto* block = targetPtr->GetComponent<BlockComponent>()) {
                damageLeft = block->ApplyDamage(damageLeft);
                if (damageLeft <= 0.0F) {
                    return;
                }
            }
            // Apply damage to ArmorComponent if it exists
            if (auto* armor = targetPtr->GetComponent<ArmorComponent>()) {
                damageLeft = armor->ApplyDamage(damageLeft);
                if (!armor->IsNotBroken()) {
                    targetPtr->RemoveComponent(armor);
                }
                if (damageLeft <= 0.0F) {
                    return;
                }
            }
            // Apply damage to HealthComponent if it exists
            if (auto* health = targetPtr->GetComponent<HealthComponent>()) {
                health->DecreaseHealth(damageLeft);
            }
        } else {
            LOG_WARN("Target not selected or expired");
        }
    }
}

void AttackComponent::SetStartupTime(const float newStartupTime) {
    assert(newStartupTime >= 0.0F && "startupTime should be positive");
    if (newStartupTime >= 0.0F) {
        startupTime = newStartupTime;
    } else {
        LOG_WARN("Trying to set negative startupTime - no changes applied");
    }
}

float AttackComponent::GetStartupTime() const { return startupTime; }

float AttackComponent::GetTimeTillAttack() const { return timeTillAttack; }

void AttackComponent::SetCooldown(const float newCoolDown) {
    assert(newCoolDown >= 0.0F && "cooldown should be positive");
    if (newCoolDown >= 0.0F) {
        cooldown = newCoolDown;
    } else {
        LOG_WARN("Trying to set negative cooldown - no changes applied");
    }
}

float AttackComponent::GetCooldwon() const { return cooldown; }

float AttackComponent::GetCurrentCooldown() const { return currentCooldown; }

void AttackComponent::SetDamage(const float newDamage) {
    assert(newDamage >= 0.0F && "damage should be positive");
    if (newDamage >= 0.0F) {
        damage = newDamage;
    } else {
        LOG_WARN("Trying to set negative damage - no changes applied");
    }
}

float AttackComponent::GetDamage() const { return damage; }

void AttackComponent::SetRange(const float newRange) {
    assert(newRange >= 0.0F && "Range should be positive");
    if (newRange >= 0.0F) {
        range = newRange;
    } else {
        LOG_WARN("Trying to set negative range - no changes applied");
    }
}

float AttackComponent::GetRange() const { return range; }

void AttackComponent::SetTarget(
    std::weak_ptr<MaxrEngine::GameObject> newTarget) {
    target = newTarget;
}

std::shared_ptr<MaxrEngine::GameObject> AttackComponent::GetTarget() const {
    if (!target.expired()) {
        return target.lock();
    }
    return std::shared_ptr<MaxrEngine::GameObject>();
}
}  // namespace Roguelike