#pragma once
#include <memory>
#include <string_view>
#include <vector>

#include "AIBlackboard.h"
#include "BTComposite.h"
#include "BTNode.h"
#include "Vector.h"
namespace Roguelike {
class BTPatrol : public BTSequenceWM {
   public:
    static constexpr std::string_view waypointsBBName = "BTPatrol_Waypoints";
    static constexpr std::string_view waypointBBName = "BTPatrol_Waypoint";
    class BTSetUpPatrolWaypoint : public BTNode {
       public:
        Status Execute(MaxrEngine::GameObject* object,
                       AIBlackboard* blackboard) override;
    };
    static void SetUpBlackboard(
        AIBlackboard* blackboard,
        std::shared_ptr<std::vector<MaxrEngine::Vector2Df>> waypoints);
    static std::unique_ptr<BTPatrol> Create(
        std::unique_ptr<BTNode>&& afterPointReach = nullptr);

   private:
    BTPatrol() = default;
};

}  // namespace Roguelike
