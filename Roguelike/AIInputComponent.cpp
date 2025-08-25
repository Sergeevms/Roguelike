#include "pch.h"

#include "AIInputComponent.h"

#include "GameObject.h"
#include "InputComponent.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace Roguelike {
AIInputComponent::AIInputComponent(MaxrEngine::GameObject* gameObject)
    : InputComponent(gameObject) {}

void AIInputComponent::Update(float deltaTime) {}

void AIInputComponent::SetDirection(const MaxrEngine::Vector2Df& newDirection) {
    auto normalizedDirection = Normalized(newDirection);
    verticalAxis = normalizedDirection.y;
    horizontalAxis = normalizedDirection.x;
    if (normalizedDirection.GetLength() > 0.0F) {
        Emit();
    }
}

MaxrEngine::Vector2Df AIInputComponent::GetDirection() const {
    return {horizontalAxis, verticalAxis};
}
}  // namespace Roguelike