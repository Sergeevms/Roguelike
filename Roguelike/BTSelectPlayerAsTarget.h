#pragma once
#include <string_view>

#include "AIBlackboard.h"
#include "BTNode.h"
#include "GameObject.h"
namespace Roguelike {
class BTSelectPlayerAsTarget : public BTNode {
   public:
    static constexpr std::string_view targetBBName = "BTTarget";
    Status Execute(MaxrEngine::GameObject* object,
                   AIBlackboard* blackboard) override;
};
}  // namespace Roguelike
