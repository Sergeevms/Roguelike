#include "pch.h"
#include "AIInputComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"

namespace MaxrEngine
{
	AIInputComponent::AIInputComponent(GameObject* gameObject)
		: InputComponent(gameObject)
	{
	}

	void AIInputComponent::Update(float deltaTime)
	{		
	}

	void MaxrEngine::AIInputComponent::SetDirection(Vector2Df direction)
	{
		auto length = direction.GetLength();
		if (length > 1.f)
		{
			direction *= 1.f / direction.GetLength();
		}		
		verticalAxis = direction.y;
		horizontalAxis = direction.x;
		if (length > 0.f)
		{
			Emit();
		}
	}

	Vector2Df AIInputComponent::GetDirection() const
	{
		return { verticalAxis, horizontalAxis };
	}
}