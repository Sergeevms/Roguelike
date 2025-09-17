#include "AIControlComponent.h"

#include <memory>
#include <utility>

#include "AIBlackboard.h"
#include "BTNode.h"
#include "Component.h"
#include "GameObject.h"
#include "Logger.h"

namespace Roguelike {
AIControlComponent::AIControlComponent(MaxrEngine::GameObject* gameObject,
                                       std::unique_ptr<BTNode>&& bTRoot)
    : Component(gameObject) {
    blackboard = gameObject->GetComponent<AIBlackboard>();
    if (blackboard == nullptr) {
        LOG_ERROR("AIBlackboard component requeried");
        gameObject->RemoveComponent(this);
    }
    root = std::move(bTRoot);
}

void AIControlComponent::Update(float deltaTime) {
    blackboard->Set(std::string(BTNode::deltaTimeBBName), deltaTime);
    if (root) {
        root->Execute(gameObject, blackboard);
    }
}

void AIControlComponent::SetBTRoot(std::unique_ptr<BTNode>&& newBTRoot) {
    root = std::move(newBTRoot);
}

}  // namespace Roguelike