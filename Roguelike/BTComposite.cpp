#include "BTComposite.h"

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "AIBlackboard.h"
#include "BTNode.h"
#include "GameObject.h"
#include "Utility.h"
namespace Roguelike {
void BTComposite::AddChild(std::unique_ptr<BTNode>&& newChild) {
    childNodes.emplace_back(std::move(newChild));
}
BTNode* BTComposite::GetChild(const int childIndex) const {
    if (InRange(childIndex, 0, static_cast<int>(childNodes.size()))) {
        return childNodes[childIndex].get();
    }
    return nullptr;
}
std::vector<BTNode*> BTComposite::GetNodes() const {
    std::vector<BTNode*> nodes;
    nodes.reserve(childNodes.size());
    for (const auto& node : childNodes) {
        nodes.push_back(node.get());
    }
    return nodes;
}
BTNode::Status BTSequenceWM::Execute(MaxrEngine::GameObject* object,
                                     AIBlackboard* blackboard) {
    // Execute children in order starting from currentChild
    for (; currentChild < childNodes.size(); ++currentChild) {
        switch (childNodes[currentChild]->Execute(object, blackboard)) {
            case Status::Success: {
                // Continue to next child on success
                break;
            }
            case Status::Running: {
                // Pause execution and return Running
                return Status::Running;
            }
            case Status::Failure: {
                // Reset and return Failure on any child failure
                currentChild = 0;
                return Status::Failure;
            }
        }
    }
    // All children succeeded - reset and return Success
    currentChild = 0;
    return Status::Success;
}
BTNode::Status BTSelectorWM::Execute(MaxrEngine::GameObject* object,
                                     AIBlackboard* blackboard) {
    // Execute children in order starting from currentChild
    for (; currentChild < childNodes.size(); ++currentChild) {
        switch (childNodes[currentChild]->Execute(object, blackboard)) {
            case Status::Success: {
                // Reset and return Success on any child success
                currentChild = 0;
                return Status::Success;
            }
            case Status::Failure: {
                // Continue to next child on failure
                break;
            }
            case Status::Running: {
                // Pause execution and return Running
                return Status::Running;
            }
        }
    }
    // All children failed - reset and return Failure
    currentChild = 0;
    return Status::Failure;
}
BTTimeRestartingSequence::BTTimeRestartingSequence(const float timeTillRestart)
    : timeTillRestart(timeTillRestart), timer(0.0F) {}
void BTTimeRestartingSequence::SetUpRestartTime(
    const float newTimeTillRestart) {
    timeTillRestart = newTimeTillRestart;
    timer = 0.0F;
}
BTNode::Status BTTimeRestartingSequence::Execute(MaxrEngine::GameObject* object,
                                                 AIBlackboard* blackboard) {
    float deltaTime = 0.0F;
    blackboard->Get(std::string(deltaTimeBBName), deltaTime);
    timer += deltaTime;
    if (timer >= timeTillRestart) {
        currentChild = 0;
    }
    return BTSequenceWM::Execute(object, blackboard);
}
BTParallel::BTParallel(const int nodesToSuccess)
    : nodesToSuccess(nodesToSuccess) {}
void BTParallel::SetUpSuccessNodesCount(const int newNodesToSuccess) {
    nodesToSuccess = newNodesToSuccess;
}
BTNode::Status BTParallel::Execute(MaxrEngine::GameObject* object,
                                   AIBlackboard* blackboard) {
    int childSuccesses = 0;
    int childFailure = 0;
    for (auto& childNodes : childNodes) {
        switch (childNodes->Execute(object, blackboard)) {
            case Status::Success:
                ++childSuccesses;
                break;
            case Status::Failure:
                ++childFailure;
                break;
            default:
                break;
        }
    }
    if (childSuccesses >= nodesToSuccess) {
        return Status::Success;
    }
    if (childFailure >= childNodes.size() - nodesToSuccess) {
        return Status::Failure;
    }
    return Status::Running;
}
BTNode::Status BTSequence::Execute(MaxrEngine::GameObject* object,
                                   AIBlackboard* blackboard) {
    for (auto& child : childNodes) {
        switch (child->Execute(object, blackboard)) {
            case Status::Success: {
                // Continue to next child on success
                break;
            }
            case Status::Running: {
                // Pause execution and return Running
                return Status::Running;
            }
            case Status::Failure: {
                // Return Failure on any child failure
                return Status::Failure;
            }
        }
    }
    // All children succeeded - return Success
    return Status::Success;
}
BTNode::Status BTSelector::Execute(MaxrEngine::GameObject* object,
                                   AIBlackboard* blackboard) {
    for (auto& child : childNodes) {
        switch (child->Execute(object, blackboard)) {
            case Status::Failure: {
                // Continue to next child on failure
                break;
            }
            case Status::Running: {
                return Status::Running;
            }
            case Status::Success: {
                return Status::Success;
            }
        }
    }
    return Status::Failure;
}
}  // namespace Roguelike