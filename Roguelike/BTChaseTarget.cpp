#include "BTChaseTarget.h"

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "AIBlackboard.h"
#include "BTDecorator.h"
#include "BTMoveAlongPath.h"
#include "BTNode.h"
#include "BTSelectPlayerAsTarget.h"
#include "GameObject.h"
#include "NavigationSystem.h"
#include "Vector.h"
namespace Roguelike {
BTNode::Status BTIsTargetClose::Execute(MaxrEngine::GameObject* object,
                                        AIBlackboard* blackboard) {
    MaxrEngine::GameObject* target;
    if (blackboard->Get(std::string(BTSelectPlayerAsTarget::targetBBName),
                        target)) {
        auto distance = (object->GetComponent<MaxrEngine::TransformComponent>()
                             ->GetWorldPosition() -
                         target->GetComponent<MaxrEngine::TransformComponent>()
                             ->GetWorldPosition())
                            .GetLength();
        if (distance <= closeDistance) {
            return Status::Success;
        }
    }
    return Status::Failure;
}
BTNode::Status BTSetUpPathToTarget::Execute(MaxrEngine::GameObject* object,
                                            AIBlackboard* blackboard) {
    MaxrEngine::GameObject* target;
    if (blackboard->Get(std::string(BTSelectPlayerAsTarget::targetBBName),
                        target)) {
        auto path = std::make_shared<std::vector<MaxrEngine::Vector2Df>>(
            NavigationSystem::Instance()->GetPath(
                object->GetComponent<MaxrEngine::TransformComponent>()
                    ->GetWorldPosition(),
                target->GetComponent<MaxrEngine::TransformComponent>()
                    ->GetWorldPosition()));
        if (!path->empty()) {
            BTMoveAlongPath::SetUpBlackboard(blackboard, path);
            return Status::Success;
        }
    }
    return Status::Failure;
}
std::unique_ptr<BTChaseTarget> BTChaseTarget::Create() {
    std::unique_ptr<BTChaseTarget> chaseTarget(new BTChaseTarget);
    chaseTarget->AddChild(
        std::make_unique<BTInverter>(std::make_unique<BTIsTargetClose>()));
    chaseTarget->AddChild(std::make_unique<BTSetUpPathToTarget>());
    chaseTarget->AddChild(BTMoveAlongPath::Create());
    return chaseTarget;
}
}  // namespace Roguelike