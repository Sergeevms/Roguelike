#pragma once
#include <string_view>

#include "AIBlackboard.h"
#include "BTNode.h"
#include "GameObject.h"
namespace Roguelike {
class BTIdle : public BTNode {
   public:
    static constexpr std::string_view durationBBName = "BTIdle_Duration";
    static constexpr std::string_view timerBBName = "BTIdle_Timer";
    static void SetUpBlackboard(AIBlackboard* blackboard,
                                const float timeToStay);
    Status Execute(MaxrEngine::GameObject* object,
                   AIBlackboard* blackboard) override;
};

class BTLookAroundIdle : public BTNode {
   public:
    static constexpr std::string_view durationBBName =
        "BTLookAroundIdle_Duration";
    static constexpr std::string_view timerBBName = "BTLookAroundIdle_Timer";
    static void SetUpBlackboard(AIBlackboard* blackboard,
                                const float timeToRotate);
    Status Execute(MaxrEngine::GameObject* object,
                   AIBlackboard* blackboard) override;
};
}  // namespace Roguelike
