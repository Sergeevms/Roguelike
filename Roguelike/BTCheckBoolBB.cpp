#include "BTCheckBoolBB.h"

#include <string>

#include "AIBlackboard.h"
#include "BTNode.h"
#include "GameObject.h"

namespace Roguelike {
BTCheckBoolBB::BTCheckBoolBB(const std::string& name) : fieldName(name) {}
BTNode::Status Roguelike::BTCheckBoolBB::Execute(MaxrEngine::GameObject* object,
                                                 AIBlackboard* blackboard) {
    bool value = false;
    if (blackboard->Get(fieldName, value) && value) {
        return Status::Success;
    }
    return Status::Failure;
}

void BTCheckBoolBB::SetFieldName(const std::string& name) { fieldName = name; }

}  // namespace Roguelike