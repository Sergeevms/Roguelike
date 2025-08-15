#include "pch.h"

#include "RigidBodyComponent.h"

#include <cmath>

#include "Component.h"
#include "GameObject.h"
#include "TransformComponent.h"

namespace MaxrEngine {
RigidBodyComponent::RigidBodyComponent(GameObject* gameObject,
                                       const bool isKinematic)
    : Component(gameObject), isKinematic(isKinematic) {
    transform = gameObject->GetComponent<TransformComponent>();
}

void RigidBodyComponent::Update(float deltaTime) {
    transform->MoveBy(linearVelocity);
    transform->RotateBy(angleVelocity);

    linearVelocity *= (1.0F - (linearDamping * deltaTime));
    angleVelocity *= (1.0F - (angleDamping * deltaTime));

    constexpr float minimalVelocity = 0.001F;

    if (fabs(linearVelocity.x) < minimalVelocity) {
        linearVelocity.x = 0.0F;
    }

    if (fabs(linearVelocity.y) < minimalVelocity) {
        linearVelocity.y = 0.0F;
    }

    if (fabs(angleVelocity) < minimalVelocity) {
        angleVelocity = 0.0F;
    }
}

void RigidBodyComponent::SetLinearVelocity(Vector2Df newLinearVelocity) {
    linearVelocity = newLinearVelocity;
}

void RigidBodyComponent::AddLinearVelocity(Vector2Df linearOffset) {
    linearVelocity += linearOffset;
}

Vector2Df RigidBodyComponent::GetLinearVelocity() const {
    return linearVelocity;
}

void RigidBodyComponent::SetAngleVelocity(float newAngleVelocity) {
    angleVelocity = newAngleVelocity;
}

void RigidBodyComponent::AddAngleVelocity(float angleOffset) {
    angleVelocity += angleOffset;
}

float RigidBodyComponent::GetAngleVelocity() const { return angleVelocity; }

void RigidBodyComponent::SetLinearDamping(float newLinearDamping) {
    linearDamping = newLinearDamping;
}

float RigidBodyComponent::GetLinearDamping() const { return linearDamping; }

void RigidBodyComponent::SetAngleDamping(float newAngleDamping) {
    angleDamping = newAngleDamping;
}

float RigidBodyComponent::GetAngleDamping() const { return angleDamping; }

void RigidBodyComponent::SetKinematic(bool newIsKinematic) {
    isKinematic = newIsKinematic;
}

bool RigidBodyComponent::GetKinematic() const { return isKinematic; }
}  // namespace MaxrEngine