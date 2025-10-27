#pragma once
#include <memory>
#include <string_view>
#include <vector>

#include "AIBlackboard.h"
#include "BTComposite.h"
#include "BTNode.h"
#include "GameObject.h"
#include "Vector.h"
namespace Roguelike {
class BTMoveAlongPath : public BTSequenceWM {
   public:
    static constexpr std::string_view pathBBName = "BTMoveAlongPath_Path";
    static constexpr std::string_view waypointBBName =
        "BTMoveAlongPath_Waypoint";
    static void SetUpBlackboard(
        AIBlackboard* blackBoard,
        std::shared_ptr<std::vector<MaxrEngine::Vector2Df>> path);
    static void Reset(AIBlackboard* blackboard);
    static std::unique_ptr<BTMoveAlongPath> Create();

   private:
    BTMoveAlongPath() = default;
};

class BTClearPath : public BTNode {
   public:
    Status Execute(MaxrEngine::GameObject* object, AIBlackboard* blackboard);
};

class BTSetPathNextWaypoint : public BTNode {
   public:
    Status Execute(MaxrEngine::GameObject* object, AIBlackboard* blackboard);
};
}  // namespace Roguelike
