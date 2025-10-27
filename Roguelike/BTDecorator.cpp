#include "BTDecorator.h"

#include <memory>
#include <utility>

#include "AIBlackboard.h"
#include "BTNode.h"
#include "GameObject.h"

namespace Roguelike {
Roguelike::BTDecorator::BTDecorator(std::unique_ptr<BTNode>&& child) {
    BTDecorator::child = std::move(child);
}
void BTDecorator::SetChild(std::unique_ptr<BTNode>&& newChild) {
    child = std::move(newChild);
}
BTNode* BTDecorator::GetChild() const {
    if (child) {
        return child.get();
    }
    return nullptr;
}
BTRepeatUntilFailure::BTRepeatUntilFailure(std::unique_ptr<BTNode>&& child)
    : BTDecorator(std::move(child)) {}
BTNode::Status BTRepeatUntilFailure::Execute(MaxrEngine::GameObject* object,
                                             AIBlackboard* blackboard) {
    if (child) {
        if (child->Execute(object, blackboard) == BTNode::Status::Failure) {
            return BTNode::Status::Success;
        }
        return BTNode::Status::Running;
    }
    return BTNode::Status::Failure;
}
BTInverter::BTInverter(std::unique_ptr<BTNode>&& child)
    : BTDecorator(std::move(child)) {}
BTNode::Status BTInverter::Execute(MaxrEngine::GameObject* object,
                                   AIBlackboard* blackboard) {
    if (child) {
        switch (child->Execute(object, blackboard)) {
            case Status::Running:
                return Status::Running;
            case Status::Failure:
                return Status::Success;
            case Status::Success:
                return Status::Failure;
        }
    }
    return Status::Success;
}
}  // namespace Roguelike