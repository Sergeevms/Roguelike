#include "AITargetSelector.h"

#include <map>
#include <memory>
#include <utility>
#include <vector>

#include "AIAttackComponent.h"
#include "AIBlackboard.h"
#include "ActorComponent.h"
#include "Component.h"
#include "GameObject.h"
#include "IObserver.h"
#include "PerceptionComponent.h"
#include "Settings.h"

namespace Roguelike {
AITargetSelector::AITargetSelector(MaxrEngine::GameObject* gameObject)
    : Component(gameObject) {}

void AITargetSelector::Update(float deltaTime) {}

void AITargetSelector::UpdateTarget() {
    auto* blackBoard = gameObject->GetComponent<AIBlackboard>();
    if (blackBoard != nullptr) {
        // Get detected actors from blackboard
        std::vector<MaxrEngine::GameObject*>* detectedActors = nullptr;
        blackBoard->Get("Detected Actors", detectedActors);

        // Add actors to map to sort them by distance
        std::map<float, MaxrEngine::GameObject*> targets;
        if (detectedActors != nullptr) {
            const auto& position =
                gameObject->GetComponent<MaxrEngine::TransformComponent>()
                    ->GetWorldPosition();

            for (auto& actor : *detectedActors) {
                // TODO(MaxrRusich) : create a list of ActorGroups that should
                // be targets
                if (actor->GetComponent<ActorComponent>()->GetGroupID() ==
                    ActorsGroups::PlayerGroup) {
                    auto between =
                        actor->GetComponent<MaxrEngine::TransformComponent>()
                            ->GetWorldPosition() -
                        position;
                    targets.emplace(std::pair<float, MaxrEngine::GameObject*>(
                        between.GetLength(), actor));
                }
            }
        }
        // Update info on target in blackboard, set current target in attack
        // component
        if (!targets.empty()) {
            blackBoard->Set("isTargetVisible", true);
            blackBoard->Set(
                "lastTargetPosition",
                targets.begin()
                    ->second->GetComponent<MaxrEngine::TransformComponent>()
                    ->GetWorldPosition());
            blackBoard->Set("lastTarget", targets.begin()->second);

            if (auto* attackComponent =
                    gameObject->GetComponent<AIAttackComponent>()) {
                attackComponent->SetTarget(
                    targets.begin()->second->weak_from_this());
            }

            Emit();
        } else {
            blackBoard->Set("isTargetVisible", false);
        }
    }
}

void AITargetSelector::Notify(
    std::shared_ptr<MaxrEngine::IObservable> observable) {
    if (std::dynamic_pointer_cast<PerceptionComponent>(observable)) {
        UpdateTarget();
    }
}
}  // namespace Roguelike