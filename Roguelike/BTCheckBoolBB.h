#pragma once
#include <string>

#include "AIBlackboard.h"
#include "BTNode.h"
#include "GameObject.h"
namespace Roguelike {
class BTCheckBoolBB : public BTNode {
    BTCheckBoolBB(const std::string& name);
    Status Execute(MaxrEngine::GameObject* object,
                   AIBlackboard* blackboard) override;
    void SetFieldName(const std::string& name);

   private:
    std::string fieldName;
};
}  // namespace Roguelike
