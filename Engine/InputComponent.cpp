#include "pch.h"

#include "InputComponent.h"

#include "Component.h"
#include "GameObject.h"

namespace MaxrEngine {
InputComponent::InputComponent(GameObject* gameObject)
    : Component(gameObject) {}

void InputComponent::Render() {}

float InputComponent::GetHorizontalAxis() const { return horizontalAxis; }

float InputComponent::GetVerticalAxis() const { return verticalAxis; }
bool InputComponent::getAttack() const { return attack; }
}  // namespace MaxrEngine