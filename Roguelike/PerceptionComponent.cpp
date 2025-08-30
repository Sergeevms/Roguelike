#include "PerceptionComponent.h"

#include <vector>

#include "ActorRegisterSystem.h"
#include "Component.h"
#include "Logger.h"
#include "PerceptionSystem.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace Roguelike {
PerceptionComponent::PerceptionComponent(MaxrEngine::GameObject* gameObject,
                                         const Parameters& parameters)
    : Component(gameObject),
      visionAngle(parameters.visionAngle),
      visionRadius(parameters.visionRadius),
      senseRadius(parameters.senseRadius),
      visionDirection(MaxrEngine::Vector2Df(parameters.visionDirectionX,
                                            parameters.visionDirectionY)) {
    transform = gameObject->GetComponent<MaxrEngine::TransformComponent>();
    PerceptionSystem::Instance()->RegisterPerceptionComponent(this);
}

PerceptionComponent::~PerceptionComponent() {
    PerceptionSystem::Instance()->UnregisterPerceptionComponent(this);
}

void PerceptionComponent::Update(float deltaTime) {}

void PerceptionComponent::SetVisionAngle(const float newVisionAngle) {
    visionAngle = newVisionAngle;
}

float PerceptionComponent::GetVisionAngle() const { return visionAngle; }

void PerceptionComponent::SetVisionRadius(const float newVisionRadius) {
    visionRadius = newVisionRadius;
}

float PerceptionComponent::GetVisionRadius() const { return visionRadius; }

void PerceptionComponent::SetSenseRadius(const float newSenseRadius) {
    senseRadius = newSenseRadius;
}

float PerceptionComponent::GetSenseRadius() const { return senseRadius; }

void PerceptionComponent::SetVisionDirection(
    const MaxrEngine::Vector2Df& newVisionDirection) {
    if (newVisionDirection.GetLength() > 0.0F) {
        visionDirection = Normalized(newVisionDirection);
    } else {
        LOG_WARN("vision direction must not be zero vector");
    }
}

const MaxrEngine::Vector2Df& PerceptionComponent::GetVisionDirection() const {
    return visionDirection;
}

const MaxrEngine::TransformComponent* PerceptionComponent::GetTransform()
    const {
    return transform;
}

void PerceptionComponent::UpdateDetectedActors() {
    const auto& actors = ActorRegisterSystem::Instance()->GetActorsList();
    UpdateDetectedActors(actors);
}

void PerceptionComponent::UpdateDetectedActors(
    const std::vector<MaxrEngine::GameObject*>& actors) {
    detectedActors.clear();
    for (const auto& actor : actors) {
        if (actor != gameObject &&
            PerceptionSystem::Instance()->CanDetect(this, actor)) {
            detectedActors.push_back(actor);
        }
    }
    Emit();
}

const std::vector<MaxrEngine::GameObject*>*
PerceptionComponent::GetDetectedActors() {
    return &detectedActors;
}
}  // namespace Roguelike
