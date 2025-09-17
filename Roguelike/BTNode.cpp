#include "BTNode.h"

#include <memory>
#include <utility>

#include "AIBlackboard.h"
#include "GameObject.h"

namespace Roguelike {
void BTComposite::AddChild(std::unique_ptr<BTNode>&& newChild) {
    childs.emplace_back(std::move(newChild));
}
void BTDecorator::SetChild(std::unique_ptr<BTNode>&& newChild) {
    child = std::move(newChild);
}
BTNode::Status BTSequence::Execute(MaxrEngine::GameObject* object,
                                   AIBlackboard* blackboard) {
    // Execute children in order starting from currentChild
    for (; currentChild < childs.size(); ++currentChild) {
        switch (childs[currentChild]->Execute(object, blackboard)) {
            case BTNode::Status::Success: {
                // Continue to next child on success
                break;
            }
            case BTNode::Status::Running: {
                // Pause execution and return Running
                return BTNode::Status::Running;
            }
            case BTNode::Status::Failure: {
                // Reset and return Failure on any child failure
                currentChild = 0;
                return BTNode::Status::Failure;
            }
        }
    }
    // All children succeeded - reset and return Success
    currentChild = 0;
    return BTNode::Status::Success;
}
BTNode::Status BTSelector::Execute(MaxrEngine::GameObject* object,
                                   AIBlackboard* blackboard) {
    // Execute children in order starting from currentChild
    for (; currentChild < childs.size(); ++currentChild) {
        switch (childs[currentChild]->Execute(object, blackboard)) {
            case BTNode::Status::Success: {
                // Reset and return Success on any child success
                currentChild = 0;
                return BTNode::Status::Success;
            }
            case BTNode::Status::Failure: {
                // Continue to next child on failure
                break;
            }
            case BTNode::Status::Running: {
                // Pause execution and return Running
                return BTNode::Status::Running;
            }
        }
    }
    // All children failed - reset and return Failure
    currentChild = 0;
    return BTNode::Status::Failure;
}
}  // namespace Roguelike
