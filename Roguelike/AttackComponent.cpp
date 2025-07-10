#include "AttackComponent.h"
#include <cassert>
#include "InputComponent.h"
#include "ArmorComponent.h"
#include "HealthComponent.h"
#include "GameObject.h"
namespace Roguelike
{
    AtackComponent::AtackComponent(MaxrEngine::GameObject* gameObject, float cooldown, float damage, float range, std::weak_ptr<MaxrEngine::GameObject> target)
        : Component(gameObject), cooldown(cooldown), damage(damage), range(range), currentCooldown(0.f), target(target)
    {
    }

    void AtackComponent::Update(float deltaTime)
    {
        if (currentCooldown > 0.f)
        {
            currentCooldown -= deltaTime;
        }
    }

    void AtackComponent::Render()
    {
    }

    void AtackComponent::Atack()
    {
        currentCooldown = cooldown;
        auto atacker = gameObject;
        if (auto targetPtr = target.lock())
        {
            auto distance = (targetPtr->GetComponent<MaxrEngine::TransformComponent>()->GetWorldPosition() -
                atacker->GetComponent<MaxrEngine::TransformComponent>()->GetWorldPosition()).GetLength();
            if (distance > range)
            {
                LOG_INFO("Target is out of atack range");
                return;
            }
            auto damageLeft = damage;
            if (auto armor = targetPtr->GetComponent<ArmorComponent>())
            {
                damageLeft = armor->ApplyDamage(damageLeft);
                if (!armor->IsNotBroken())
                {
                    targetPtr->RemoveComponent(armor);
                }
            }
            if (damageLeft > 0.f)
            {
                if (auto health = targetPtr->GetComponent<HealthComponent>())
                {
                    health->DecreaseHealth(damageLeft);
                }
            }
        }
        else
        {
            LOG_WARN("Target not selected or expired");
        }
    }

    void AtackComponent::SetCooldown(const float newCoolDown)
    {
        assert(newCoolDown >= 0.f && "cooldown should be positive");
        if (newCoolDown >= 0.f)
        {
            cooldown = newCoolDown;
        }
        else
        {
            LOG_WARN("Trying to set negative cooldown - no changes applied");
        }
    }

    float AtackComponent::GetCooldwon() const
    {
        return cooldown;
    }

    void AtackComponent::SetDamage(const float newDamage)
    {
        assert(newDamage >= 0.f && "damage should be positive");
        if (newDamage >= 0.f)
        {
            damage = newDamage;
        }
        else
        {
            LOG_WARN("Trying to set negative damage - no changes applied");
        }
    }

    float AtackComponent::GetDamage() const
    {
        return damage;
    }

    void AtackComponent::SetRange(const float newRange)
    {
        assert(newRange >= 0.f && "Range should be positive");
        if (newRange >= 0.f)
        {
            range = newRange;
        }
        else
        {
            LOG_WARN("Trying to set negative range - no changes applied");
        }
    }

    float AtackComponent::GetRange() const
    {
        return range;
    }

    void AtackComponent::SetTarget(std::weak_ptr<MaxrEngine::GameObject> newTarget)
    {
        target = newTarget;
    }

    std::shared_ptr<MaxrEngine::GameObject> AtackComponent::GetTarget() const
    {
        if (!target.expired())
        {
            return target.lock();
        }
        return std::shared_ptr<MaxrEngine::GameObject>();
    }
}