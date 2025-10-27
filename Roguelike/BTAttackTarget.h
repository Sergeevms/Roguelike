#pragma once
#include "BTNode.h"
namespace Roguelike {
class BTAttackTarget : public BTNode {
    Status Execute(MaxrEngine::GameObject* object,
                   AIBlackboard* blackboard) override;
};
}  // namespace Roguelike
