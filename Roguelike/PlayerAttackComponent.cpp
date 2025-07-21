#include "PlayerAttackComponent.h"

#include <map>
#include <memory>
#include <utility>

#include "ActorRegisterSystem.h"
#include "AttackComponent.h"
#include "GameObject.h"
#include "IObserver.h"
#include "InputComponent.h"
#include "Logger.h"
#include "Settings.h"

namespace Roguelike {
PlayerAttackComponent::PlayerAttackComponent(
    MaxrEngine::GameObject* gameObject,
    const AtackComponentParameters& atackParameters,
    std::weak_ptr<MaxrEngine::GameObject> target)
    : AttackComponent(gameObject, atackParameters, target) {}

void PlayerAttackComponent::Notify(
    std::shared_ptr<MaxrEngine::IObservable> observable) {
    if (auto input =
            std::dynamic_pointer_cast<MaxrEngine::InputComponent>(observable)) {
        if (currentCooldown <= 0.0F) {
            currentCooldown = cooldown;
            auto position =
                gameObject->GetComponent<MaxrEngine::TransformComponent>()
                    ->GetWorldPosition();
            auto targetsVector =
                ActorRegisterSystem::Instance()->GetActorsNotInGroupList(
                    ActorsGroups::PlayerGroup);
            std::map<float, MaxrEngine::GameObject*> targets;
            for (auto& possibleTarget : targetsVector) {
                targets.emplace(std::pair<float, MaxrEngine::GameObject*>(
                    (possibleTarget
                         ->GetComponent<MaxrEngine::TransformComponent>()
                         ->GetWorldPosition() -
                     position)
                        .GetLength(),
                    possibleTarget));
            }
            auto newTarget = targets.begin();
            if (newTarget->first > range) {
                LOG_INFO("Closest target out of range");
            } else {
                target = newTarget->second->weak_from_this();
                Attack();
            }
        } else {
            LOG_INFO("Attack is on cooldown");
        }
    }
}
}  // namespace Roguelike
