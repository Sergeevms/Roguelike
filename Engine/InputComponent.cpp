#include "pch.h"
#include "InputComponent.h"

namespace MaxrEngine
{
	InputComponent::InputComponent(GameObject* gameObject) : Component(gameObject) {}

	void InputComponent::Render() {}

	float InputComponent::GetHorizontalAxis() const
	{
		return horizontalAxis;
	}

	float InputComponent::GetVerticalAxis() const
	{
		return verticalAxis;
	}
}