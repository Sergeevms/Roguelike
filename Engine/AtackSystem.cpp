#include "pch.h"
#include "AtackSystem.h"
#include "AtackComponent.h"
#include "GameObject.h"
#include "ArmorComponent.h"
#include "HealthComponent.h"

namespace MaxrEngine
{
    AtackSystem* AtackSystem::Instance()
    {
        static AtackSystem instance;
        return &instance;
    }

    void MaxrEngine::AtackSystem::OneTargetAtack(AtackComponent* atackComponent, GameObject* target)
    {
        auto atacker = atackComponent->GetGameObject();
        auto distance = (target->GetComponent<TransformComponent>()->GetWorldPosition() - atacker->GetComponent<TransformComponent>()->GetWorldPosition()).GetLength();
        if (distance > atackComponent->GetRange())
        {
            LOG_INFO("Target is out of atack range");
            return;
        }
        auto damageLeft = atackComponent->GetDamage();
        if (auto armor = target->GetComponent<ArmorComponent>())
        {
            damageLeft = armor->ApplyDamage(damageLeft);
            if (!armor->IsNotBroken())
            {
                target->RemoveComponent(armor);
            }
        }
        if (damageLeft > 0.f)
        {
            if (auto health = target->GetComponent<HealthComponent>())
            {
                health->DecreaseHealth(damageLeft);
            }
        }
    }
}