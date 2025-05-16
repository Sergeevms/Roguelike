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
		if (auto length = direction.GetLength() > 1.f)
		{
			direction *= 1.f / direction.GetLength();
		}		
		verticalAxis = direction.y;
		horizontalAxis = direction.x;
	}
}