#include "pch.h"

#include "MovementComponent.h"

#include "Component.h"
#include "GameObject.h"
#include "InputComponent.h"
#include "Logger.h"
#include "SpriteAnimationComponent.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace MaxrEngine {
MovementComponent::MovementComponent(GameObject* gameObject)
    : Component(gameObject) {
    input = gameObject->GetComponent<InputComponent>();
    transform = gameObject->GetComponent<TransformComponent>();

    if (input == nullptr) {
        LOG_ERROR("Need InputComponent for movement.");
        gameObject->RemoveComponent(this);
    }
}

void MovementComponent::Update(float deltaTime) {
    const Vector2Df direction =
        Vector2Df{input->GetHorizontalAxis(), input->GetVerticalAxis()};

    transform->MoveBy(speed * deltaTime * direction);

    acceleration = transform->GetWorldPosition() - previosPosition;
    previosPosition = transform->GetWorldPosition();
    if (auto* animationComponent =
            gameObject->GetComponent<SpriteAnimationComponent>()) {
        if (direction.GetLength() > 0.0F) {
            animationComponent->StartAnimation("Walk");
        } else {
            animationComponent->StartAnimation("Idle");
        }
    }
}
void MovementComponent::Render() {}

void MovementComponent::SetSpeed(float newSpeed) { speed = newSpeed; }

float MovementComponent::GetSpeed() const { return speed; }

float MovementComponent::GetAccelerationSquared() const {
    const Vector2Df squaredAcceleration = acceleration * acceleration;
    return squaredAcceleration.x + squaredAcceleration.y;
}
}  // namespace MaxrEngine