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
constexpr float succesDistance = 0.01F;

void BTMoveToPoint::SetUpBlackboard(AIBlackboard* blackboard,
                                    const MaxrEngine::Vector2Df& target) {
    blackboard->Set(std::string(targetBBName),
                    std::optional<MaxrEngine::Vector2Df>(target));
}
BTNode::Status Roguelike::BTMoveToPoint::Execute(MaxrEngine::GameObject* object,
                                                 AIBlackboard* blackboard) {
    std::optional<MaxrEngine::Vector2Df> targetPoint;
    // Check if moving point setted up
    if (blackboard->Get(std::string(targetBBName), targetPoint) &&
        targetPoint) {
        const auto& objectPosition =
            object->GetComponent<MaxrEngine::TransformComponent>()
                ->GetWorldPosition();
        const auto betweenVector = *targetPoint - objectPosition;
        auto* input = object->GetComponent<AIInputComponent>();
        // If reached point - return Success
        if (betweenVector.GetLength() < succesDistance) {
            targetPoint.reset();
            blackboard->Set(std::string(targetBBName), targetPoint);
            input->SetDirection({0, 0});
            return BTNode::Status::Success;
        }
        // Set up mving direction and return Runnig if still moving to point
        input->SetDirection(betweenVector);
        return BTNode::Status::Running;
    }
    return BTNode::Status::Failure;
}
}  // namespace Roguelike
