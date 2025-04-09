#include "pch.h"
#include "TransformComponent.h"

namespace MaxrEngine
{
	TransformComponent::TransformComponent(GameObject* gameObject) : Component(gameObject) {}

	void TransformComponent::Update(float deltaTime)
	{
	}

	void TransformComponent::Render()
	{
	}

	void TransformComponent::MoveBy(const Vector2Df& offset)
	{
		position += offset;
	}

	void TransformComponent::RotateBy(const float offset)
	{
		rotation += offset;
		while (rotation >= 360.f)
		{
			rotation -= 360.f;
		}
		while (rotation < 0.f)
		{
			rotation += 360.f;
		}
	}

	void TransformComponent::ScaleBy(const Vector2Df& offset)
	{
		scale *= offset;
	}

	const Vector2Df TransformComponent::GetWorldPosition() const
	{
		return position;
	}
	const float TransformComponent::GetWorldRotation() const
	{
		return rotation;
	}
	const Vector2Df TransformComponent::GetWorldScale() const
	{
		return scale;
	}
}