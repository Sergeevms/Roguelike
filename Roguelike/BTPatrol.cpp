#include "BTPatrol.h"

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "AIBlackboard.h"
#include "BTDecorator.h"
#include "BTMoveAlongPath.h"
#include "BTNode.h"
#include "GameObject.h"
#include "NavigationSystem.h"
#include "Vector.h"

namespace Roguelike {
BTNode::Status BTPatrol::BTSetUpPatrolWaypoint::Execute(
    MaxrEngine::GameObject* object, AIBlackboard* blackboard) {
    std::shared_ptr<std::vector<MaxrEngine::Vector2Df>> waypoints;
    int currentWaypoint;
    if (blackboard->Get(std::string(waypointsBBName), waypoints) &&
        !waypoints->empty() &&
        blackboard->Get(std::string(waypointBBName), currentWaypoint)) {
        currentWaypoint =
            (currentWaypoint + 1) % static_cast<int>(waypoints->size());
        const auto& currentPosition =
            object->GetComponent<MaxrEngine::TransformComponent>()
                ->GetWorldPosition();
        auto path = std::make_shared<std::vector<MaxrEngine::Vector2Df>>(
            NavigationSystem::Instance()->GetPath(
                currentPosition, (*waypoints)[currentWaypoint]));
        BTMoveAlongPath::SetUpBlackboard(blackboard, path);
        blackboard->Set(std::string(waypointBBName), currentWaypoint);
        return BTNode::Status::Success;
    }
    return BTNode::Status::Failure;
}
void BTPatrol::SetUpBlackboard(
    AIBlackboard* blackboard,
    std::shared_ptr<std::vector<MaxrEngine::Vector2Df>> waypoints) {
    blackboard->Set(std::string(waypointsBBName), waypoints);
    blackboard->Set(std::string(waypointBBName), -1);
}
std::unique_ptr<BTPatrol> BTPatrol::Create(
    std::unique_ptr<BTNode>&& afterPointReach) {
    auto patrol = std::unique_ptr<BTPatrol>(new BTPatrol);
    patrol->AddChild(std::make_unique<BTSetUpPatrolWaypoint>());
    auto repeat = std::make_unique<BTRepeatUntilFailure>();
    repeat->SetChild(BTMoveAlongPath::Create());
    patrol->AddChild(std::move(repeat));
    if (afterPointReach) {
        patrol->AddChild(std::move(afterPointReach));
    }
    return patrol;
}
}  // namespace Roguelike