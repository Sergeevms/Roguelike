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

	void MaxrEngine::AIInputComponent::SetDirection(Vector2Df newDirection)
	{
		auto length = newDirection.GetLength();
		if (length > 1.f)
		{
			newDirection *= 1.f / newDirection.GetLength();
		}		
		verticalAxis = newDirection.y;
		horizontalAxis = newDirection.x;
		if (length > 0.f)
		{
			Emit();
		}
	}

	Vector2Df AIInputComponent::GetDirection() const
	{
		return { horizontalAxis, verticalAxis  };
	}
}