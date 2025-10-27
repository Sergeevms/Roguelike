#include "BTMoveToPoint.h"

#include <optional>
#include <string>
#include <string_view>

#include "AIBlackboard.h"
#include "AIInputComponent.h"
#include "BTNode.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace Roguelike {
constexpr float successDistance = 0.5F;

void BTMoveToPoint::SetUpBlackboard(AIBlackboard* blackboard,
                                    const MaxrEngine::Vector2Df& target) {
    blackboard->Set(std::string(targetBBName),
                    std::optional<MaxrEngine::Vector2Df>(target));
}
void BTMoveToPoint::Reset(MaxrEngine::GameObject* object,
                          AIBlackboard* blackboard) {
    const std::optional<MaxrEngine::Vector2Df> targetPoint;
    blackboard->Set(std::string(targetBBName), targetPoint);
    auto* input = object->GetComponent<AIInputComponent>();
    input->SetDirection({0, 0});
}
BTNode::Status Roguelike::BTMoveToPoint::Execute(MaxrEngine::GameObject* object,
                                                 AIBlackboard* blackboard) {
    std::optional<MaxrEngine::Vector2Df> targetPoint;
    // Check if moving point is set up
    if (blackboard->Get(std::string(targetBBName), targetPoint) &&
        targetPoint) {
        const auto& objectPosition =
            object->GetComponent<MaxrEngine::TransformComponent>()
                ->GetWorldPosition();
        const auto betweenVector = *targetPoint - objectPosition;
        auto* input = object->GetComponent<AIInputComponent>();
        // If reached point - return Success
        if (betweenVector.GetLength() < successDistance) {
            Reset(object, blackboard);
            return Status::Success;
        }
        // Set up moving direction and return Running if still moving to point
        input->SetDirection(betweenVector);
        return Status::Running;
    }
    return Status::Failure;
}
}  // namespace Roguelike
