#include "AttackComponent.h"

#include <cassert>

#include "ArmorComponent.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "InputComponent.h"
namespace Roguelike {
AttackComponent::AttackComponent(MaxrEngine::GameObject* gameObject,
                                 float cooldown, float damage, float range,
                                 std::weak_ptr<MaxrEngine::GameObject> target)
    : Component(gameObject),
      cooldown(cooldown),
      damage(damage),
      range(range),
      currentCooldown(0.f),
      target(target) {}

void AttackComponent::Update(float deltaTime) {
    if (currentCooldown > 0.f) {
        currentCooldown -= deltaTime;
    }
}

void AttackComponent::Render() {}

void AttackComponent::Attack() {
    currentCooldown = cooldown;
    auto attacker = gameObject;
    if (auto targetPtr = target.lock()) {
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
        if (auto armor = targetPtr->GetComponent<ArmorComponent>()) {
            damageLeft = armor->ApplyDamage(damageLeft);
            if (!armor->IsNotBroken()) {
                targetPtr->RemoveComponent(armor);
            }
        }
        if (damageLeft > 0.f) {
            if (auto health = targetPtr->GetComponent<HealthComponent>()) {
                health->DecreaseHealth(damageLeft);
            }
        }
    } else {
        LOG_WARN("Target not selected or expired");
    }
}

void AttackComponent::SetCooldown(const float newCoolDown) {
    assert(newCoolDown >= 0.f && "cooldown should be positive");
    if (newCoolDown >= 0.f) {
        cooldown = newCoolDown;
    } else {
        LOG_WARN("Trying to set negative cooldown - no changes applied");
    }
}

float AttackComponent::GetCooldwon() const { return cooldown; }

void AttackComponent::SetDamage(const float newDamage) {
    assert(newDamage >= 0.f && "damage should be positive");
    if (newDamage >= 0.f) {
        damage = newDamage;
    } else {
        LOG_WARN("Trying to set negative damage - no changes applied");
    }
}

float AttackComponent::GetDamage() const { return damage; }

void AttackComponent::SetRange(const float newRange) {
    assert(newRange >= 0.f && "Range should be positive");
    if (newRange >= 0.f) {
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