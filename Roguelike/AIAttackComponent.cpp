#include "AIAttackComponent.h"

#include <memory>

#include "AIBlackboard.h"
#include "AttackComponent.h"
#include "GameObject.h"

namespace Roguelike {
AIAttackComponent::AIAttackComponent(
    MaxrEngine::GameObject* gameObject, const Parameters& atackParameters,
    std::weak_ptr<MaxrEngine::GameObject> target)
    : AttackComponent(gameObject, atackParameters, target) {}

void AIAttackComponent::Update(float deltaTime) {
    AttackComponent::Update(deltaTime);
    bool targetVisible = false;
    auto* blackBoard = gameObject->GetComponent<AIBlackboard>();
    if (currentCooldown <= 0.0F &&
        blackBoard->Get("isTargetVisible", targetVisible) && targetVisible) {
        if (!target.expired()) {
            auto targetPtr = target.lock();
            auto distance =
                (gameObject->GetComponent<MaxrEngine::TransformComponent>()
                     ->GetWorldPosition() -
                 targetPtr->GetComponent<MaxrEngine::TransformComponent>()
                     ->GetWorldPosition())
                    .GetLength();
            if (distance <= range) {
                StartAttack();
            }
        }
    }
}
}  // namespace Roguelike