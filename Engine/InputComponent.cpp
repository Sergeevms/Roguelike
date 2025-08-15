#include "pch.h"

#include "InputComponent.h"

#include "Component.h"
#include "GameObject.h"

namespace MaxrEngine {
InputComponent::InputComponent(GameObject* gameObject)
    : Component(gameObject) {}

float InputComponent::GetHorizontalAxis() const { return horizontalAxis; }

float InputComponent::GetVerticalAxis() const { return verticalAxis; }
bool InputComponent::getAttack() const { return attack; }
bool InputComponent::getBlock() const { return block; }
}  // namespace MaxrEngine