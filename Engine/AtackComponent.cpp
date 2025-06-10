#include "pch.h"
#include "AtackComponent.h"
#include <cassert>
#include "InputComponent.h"
#include "AtackSystem.h"
namespace MaxrEngine
{
    AtackComponent::AtackComponent(GameObject* gameObject, float cooldown, float damage, float range, GameObject* tartget)
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

    void MaxrEngine::AtackComponent::SetTarget(GameObject* newTarget)
    {
        target = newTarget;
    }

    GameObject* AtackComponent::GetTarget() const
    {
        return target;
    }

    void AtackComponent::Notify(std::shared_ptr<IObservable> observable)
    {
        if (auto inputComponent = std::dynamic_pointer_cast<InputComponent>(observable))
        {
            if (inputComponent->getAtack())
            {
                if (currentCooldown > 0.f)
                {
                    LOG_INFO("Atack is on cooldown!");
                }
                else
                {
                    currentCooldown = cooldown;
                    if (target)
                    {
                        AtackSystem::Instance()->OneTargetAtack(this, target);
                    }
                    else
                    {
                        LOG_WARN("Target not set!")
                    }
                }
            }
        }
    }
}