#include "AIPerceptionComponent.h"

#include <memory>
#include <string>
#include <vector>

#include "AIBlackboard.h"
#include "AIInputComponent.h"
#include "GameObject.h"
#include "IObserver.h"
#include "Logger.h"
#include "PerceptionComponent.h"

namespace Roguelike {

AIPerceptionComponent::AIPerceptionComponent(
    MaxrEngine::GameObject* gameObject,
    const PerceptionComponent::Parameters& parameters)
    : PerceptionComponent(gameObject, parameters) {
    auto* blackBoard = gameObject->GetComponent<AIBlackboard>();
    if (blackBoard != nullptr) {
        blackBoard->Set(std::string(detectedActorsBBName), &detectedActors);
    } else {
        LOG_ERROR("AIBlackboard required for AIPerceptionComponent");
        gameObject->RemoveComponent(this);
        return;
    }
}

void AIPerceptionComponent::UpdateDetectedActors(
    const std::vector<MaxrEngine::GameObject*>& actors) {
    PerceptionComponent::UpdateDetectedActors(actors);
    auto* blackBoard = gameObject->GetComponent<AIBlackboard>();
    if (blackBoard != nullptr) {
        if (!detectedActors.empty()) {
            blackBoard->Set(std::string(isActorsDetectedBBName), true);
        } else {
            blackBoard->Set(std::string(isActorsDetectedBBName), false);
        }
    }
}

void AIPerceptionComponent::Notify(std::shared_ptr<IObservable> observable) {
    if (auto input = std::dynamic_pointer_cast<AIInputComponent>(observable)) {
        SetVisionDirection(input->GetDirection());
    }
}
}  // namespace Roguelike
