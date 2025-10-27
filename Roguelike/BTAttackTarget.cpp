#include "BTAttackTarget.h"

#include <string>

#include "AIBlackboard.h"
#include "AttackComponent.h"
#include "BTNode.h"
#include "BTSelectPlayerAsTarget.h"
#include "GameObject.h"
namespace Roguelike {
BTNode::Status BTAttackTarget::Execute(MaxrEngine::GameObject* object,
                                       AIBlackboard* blackboard) {
    auto* attackComponent = object->GetComponent<AttackComponent>();
    if (attackComponent == nullptr) {
        return Status::Failure;
    }

    MaxrEngine::GameObject* target = nullptr;
    if (blackboard->Get(std::string(BTSelectPlayerAsTarget::targetBBName),
                        target) &&
        target != nullptr) {
        if (attackComponent->GetCurrentCooldown() > 0.0F) {
            return Status::Failure;
        }
        const auto distance =
            (target->GetComponent<MaxrEngine::TransformComponent>()
                 ->GetWorldPosition() -
             object->GetComponent<MaxrEngine::TransformComponent>()
                 ->GetWorldPosition())
                .GetLength();
        if (distance > attackComponent->GetRange()) {
            return Status::Failure;
        }
        attackComponent->SetTarget(target->weak_from_this());
        attackComponent->StartAttack();
        return Status::Success;
    }
    return Status::Failure;
}
}  // namespace Roguelike