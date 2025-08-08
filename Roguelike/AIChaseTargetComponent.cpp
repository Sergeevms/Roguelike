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
    // NOLINTEND(misc-unused-parameters) : overrided method
    auto* blackBoard = gameObject->GetComponent<AIBlackboard>();
    if (blackBoard != nullptr) {
        bool isTargetVisible = false;
        MaxrEngine::Vector2Df movingDirection;
        auto* inputComponent =
            gameObject->GetComponent<MaxrEngine::AIInputComponent>();
        if (blackBoard->Get("isTargetVisible", isTargetVisible) &&
            isTargetVisible) {
            auto* transform =
                gameObject->GetComponent<MaxrEngine::TransformComponent>();
            MaxrEngine::GameObject* target = nullptr;
            if (blackBoard->Get("lastTarget", target)) {
                auto betweenVector =
                    target->GetComponent<MaxrEngine::TransformComponent>()
                        ->GetWorldPosition() -
                    transform->GetWorldPosition();
                auto distance = betweenVector.GetLength();
                if (InRange(distance, minumumChaseRadius, maximumChaseRadius)) {
                    movingDirection = betweenVector;
                }
            }
        }
        inputComponent->SetDirection(movingDirection);
    } else {
        LOG_ERROR("AIBlackboard requried for AIChaseComponent");
    }
}

void AIChaseTargetComponent::Render() {}

void AIChaseTargetComponent::SetMaximumChaseRadius(float newMaximumRadius) {
    maximumChaseRadius = newMaximumRadius;
}

void AIChaseTargetComponent::SetMinimumChaseRadius(float newMinimuRadius) {
    minumumChaseRadius = newMinimuRadius;
}
}  // namespace Roguelike