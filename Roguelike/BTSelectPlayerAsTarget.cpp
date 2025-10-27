#include "BTSelectPlayerAsTarget.h"

#include <string>
#include <vector>

#include "AIBlackboard.h"
#include "AIPerceptionComponent.h"
#include "ActorComponent.h"
#include "BTNode.h"
#include "GameObject.h"
#include "Settings.h"

namespace Roguelike {
BTNode::Status BTSelectPlayerAsTarget::Execute(MaxrEngine::GameObject* object,
                                               AIBlackboard* blackboard) {
    bool isActorsDetected;
    if (blackboard->Get(
            std::string(AIPerceptionComponent::isActorsDetectedBBName),
            isActorsDetected) &&
        isActorsDetected) {
        std::vector<MaxrEngine::GameObject*>* actorsDetected;
        if (blackboard->Get(
                std::string(AIPerceptionComponent::detectedActorsBBName),
                actorsDetected)) {
            for (auto* actor : *actorsDetected) {
                const auto actorGroup =
                    actor->GetComponent<ActorComponent>()->GetGroupID();
                if (actorGroup == Settings::ActorsGroups::Player) {
                    blackboard->Set(std::string(targetBBName), actor);
                    return Status::Success;
                }
            }
        }
    }
    MaxrEngine::GameObject* noTarget = nullptr;
    blackboard->Set(std::string(targetBBName), noTarget);
    return Status::Failure;
}
}  // namespace Roguelike