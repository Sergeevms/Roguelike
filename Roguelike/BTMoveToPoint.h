#pragma once
#include <string_view>

#include "AIBlackboard.h"
#include "BTNode.h"
#include "GameObject.h"
#include "Vector.h"

namespace Roguelike {
class BTMoveToPoint : public BTNode {
   public:
    static constexpr std::string_view targetBBName = "BTMoveToPoint_target";
    static void SetUpBlackboard(AIBlackboard* blackboard,
                                const MaxrEngine::Vector2Df& target);
    static void Reset(MaxrEngine::GameObject* object, AIBlackboard* blackboard);

    Status Execute(MaxrEngine::GameObject* object,
                   AIBlackboard* blackboard) override;
};
}  // namespace Roguelike
