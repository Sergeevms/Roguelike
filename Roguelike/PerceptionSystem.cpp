#include "PerceptionSystem.h"

#include <algorithm>

#include "ActorRegisterSystem.h"
#include "GameObject.h"
#include "OpaqueComponent.h"
#include "PerceptionComponent.h"
#include "Utility.h"
#include "Vector.h"

namespace Roguelike {
PerceptionSystem* PerceptionSystem::Instance() {
    static PerceptionSystem instance;
    return &instance;
}

void PerceptionSystem::Update() {
    const auto& actors = ActorRegisterSystem::Instance()->GetActorsList();
    for (auto& component : perceptionComponents) {
        component->UpdateDetectedActors(actors);
    }
}

bool PerceptionSystem::CanDetect(PerceptionComponent* perceptionComponent,
                                 MaxrEngine::GameObject* target) const {
    const auto& perceptionPosition =
        perceptionComponent->GetTransform()->GetWorldPosition();
    const auto& targetPosition =
        target->GetComponent<MaxrEngine::TransformComponent>()
            ->GetWorldPosition();
    const MaxrEngine::Vector2Df betweenVector =
        targetPosition - perceptionPosition;
    const float distance = betweenVector.GetLength();
    if (distance <= perceptionComponent->GetSenseRadius()) {
        return true;
    }
    if (distance > perceptionComponent->GetVisionRadius()) {
        return false;
    }
    const float angle =
        AngleDegree(perceptionComponent->GetVisionDirection(), betweenVector);
    if (angle > Half(perceptionComponent->GetVisionAngle())) {
        return false;
    }
    return LineClear(perceptionPosition, targetPosition);
}

bool PerceptionSystem::LineClear(const MaxrEngine::Vector2Df& startPoint,
                                 const MaxrEngine::Vector2Df& endPoint) const {
    auto direction = endPoint - startPoint;
    auto directionLength = direction.GetLength();
    direction = MaxrEngine::Normalized(direction);
    const float invDirX = 1.0F / direction.x;
    const bool positiveX = invDirX >= 0.0F;
    const float invDirY = 1.0F / direction.y;
    const bool positiveY = invDirY >= 0.0F;

    for (const auto& opaque : opaqueComponents) {
        float tMin = 0.0F;
        float tMax = directionLength;
        const float tMinX =
            ((positiveX ? opaque->bounds.left
                        : opaque->bounds.left + opaque->bounds.width) -
             startPoint.x) *
            invDirX;
        const float tMaxX =
            ((positiveX ? opaque->bounds.left + opaque->bounds.width
                        : opaque->bounds.left) -
             startPoint.x) *
            invDirX;
        if (tMin > tMaxX || tMax < tMinX) {
            continue;
        }
        tMin = std::max(tMin, tMinX);
        tMax = std::min(tMax, tMaxX);
        const float tMinY =
            ((positiveY ? opaque->bounds.top
                        : opaque->bounds.top + opaque->bounds.height) -
             startPoint.y) *
            invDirY;
        const float tMaxY =
            ((positiveY ? opaque->bounds.top + opaque->bounds.height
                        : opaque->bounds.top) -
             startPoint.y) *
            invDirY;
        if (tMin > tMaxY || tMax < tMinY) {
            continue;
        }
        return false;
    }
    return true;
}

void PerceptionSystem::RegisterOpaqueComponent(OpaqueComponent* component) {
    opaqueComponents.push_back(component);
}

void PerceptionSystem::UnregisterOpaqueComponent(OpaqueComponent* component) {
    opaqueComponents.erase(
        std::remove_if(
            opaqueComponents.begin(), opaqueComponents.end(),
            [component](OpaqueComponent* comp) { return component == comp; }),
        opaqueComponents.end());
}

void PerceptionSystem::RegisterPerceptionComponent(
    PerceptionComponent* component) {
    perceptionComponents.push_back(component);
}

void PerceptionSystem::UnregisterPerceptionComponent(
    PerceptionComponent* component) {
    perceptionComponents.erase(
        std::remove_if(perceptionComponents.begin(), perceptionComponents.end(),
                       [component](PerceptionComponent* comp) {
                           return component == comp;
                       }),
        perceptionComponents.end());
}

void PerceptionSystem::ClearOpaqueObjects() { opaqueComponents.clear(); }

void PerceptionSystem::ClearPerceptionComponents() {
    perceptionComponents.clear();
}

void PerceptionSystem::Clear() {
    ClearOpaqueObjects();
    ClearPerceptionComponents();
}
}  // namespace Roguelike