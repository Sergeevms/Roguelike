#include "AIChaseTargetComponent.h"

#include "AIBlackboard.h"
#include "AIInputComponent.h"
#include "Component.h"
#include "GameObject.h"
#include "Logger.h"
#include "TransformComponent.h"
#include "Utility.h"
#include "Vector.h"

namespace Roguelike {
Roguelike::AIChaseTargetComponent::AIChaseTargetComponent(
    MaxrEngine::GameObject* gameObject, const Parameters& parameters)
    : Component(gameObject),
      minumumChaseRadius(parameters.minumumChaseRadius),
      maximumChaseRadius(parameters.maximumChaseRadius) {}

// NOLINTBEGIN(misc-unused-parameters) : overrided virtual method
void AIChaseTargetComponent::Update(float deltaTime) {
    // Check that we have access to blackboard
    auto* blackBoard = gameObject->GetComponent<AIBlackboard>();
    if (blackBoard != nullptr) {
        // Create new moving direction, {0, 0} (not moving) by default
        MaxrEngine::Vector2Df movingDirection;

        // Check that target visible and setted
        bool isTargetVisible = false;
        MaxrEngine::GameObject* target = nullptr;
        if (blackBoard->Get("isTargetVisible", isTargetVisible) &&
            isTargetVisible && blackBoard->Get("lastTarget", target) &&
            target != nullptr) {
            // Get vector between self and target
            auto betweenVector =
                target->GetComponent<MaxrEngine::TransformComponent>()
                    ->GetWorldPosition() -
                gameObject->GetComponent<MaxrEngine::TransformComponent>()
                    ->GetWorldPosition();

            // Check distance between target and self, update moving direction
            // if needed.
            auto distance = betweenVector.GetLength();
            if (InRange(distance, minumumChaseRadius, maximumChaseRadius)) {
                movingDirection = betweenVector;
            }
        }
        // Update moving direction in input component
        auto* inputComponent =
            gameObject->GetComponent<AIInputComponent>();
        inputComponent->SetDirection(movingDirection);
    } else {
        LOG_ERROR("AIBlackboard requried for AIChaseComponent");
    }
}
// NOLINTEND(misc-unused-parameters) : overrided method

void AIChaseTargetComponent::SetMaximumChaseRadius(float newMaximumRadius) {
    maximumChaseRadius = newMaximumRadius;
}

void AIChaseTargetComponent::SetMinimumChaseRadius(float newMinimuRadius) {
    minumumChaseRadius = newMinimuRadius;
}
}  // namespace Roguelike