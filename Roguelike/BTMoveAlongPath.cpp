#include "BTMoveAlongPath.h"

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "AIBlackboard.h"
#include "BTMoveToPoint.h"
#include "BTNode.h"
#include "GameObject.h"
#include "Vector.h"

namespace Roguelike {

void BTMoveAlongPath::SetUpBlackboard(
    AIBlackboard* blackBoard,
    std::shared_ptr<std::vector<MaxrEngine::Vector2Df>> path) {
    blackBoard->Set(std::string(waypointBBName), -1);
    blackBoard->Set(std::string(pathBBName), path);
}

std::unique_ptr<BTMoveAlongPath> BTMoveAlongPath::Create() {
    std::unique_ptr<BTMoveAlongPath> moveNode =
        std::unique_ptr<BTMoveAlongPath>(new BTMoveAlongPath);
    moveNode->AddChild(std::make_unique<BTSetPathNextWaypoint>());
    moveNode->AddChild(std::make_unique<BTMoveToPoint>());
    return moveNode;
}
void BTMoveAlongPath::Reset(AIBlackboard* blackboard) {
    SetUpBlackboard(blackboard, nullptr);
};

BTNode::Status BTSetPathNextWaypoint::Execute(MaxrEngine::GameObject* object,
                                              AIBlackboard* blackboard) {
    std::shared_ptr<std::vector<MaxrEngine::Vector2Df>> path;
    if (blackboard->Get(std::string(BTMoveAlongPath::pathBBName), path) &&
        path) {
        int currentWaypoint;
        if (blackboard->Get(std::string(BTMoveAlongPath::waypointBBName),
                            currentWaypoint)) {
            ++currentWaypoint;
            if (currentWaypoint >= path->size()) {
                path = nullptr;
                return BTNode::Status::Failure;
            }
            blackboard->Set(std::string(BTMoveAlongPath::waypointBBName),
                            currentWaypoint);
            BTMoveToPoint::SetUpBlackboard(blackboard,
                                           (*path)[currentWaypoint]);
            return BTNode::Status::Success;
        }
    }
    return BTNode::Status::Failure;
};

BTNode::Status BTClearPath::Execute(MaxrEngine::GameObject* object,
                                    AIBlackboard* blackboard) {
    BTMoveAlongPath::Reset(blackboard);
    BTMoveToPoint::Reset(object, blackboard);
    return Status::Success;
};
}  // namespace Roguelike