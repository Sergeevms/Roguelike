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
		auto transform = gameObject->GetComponent<TransformComponent>();
		auto direction = target - transform->GetWorldPosition();
		direction *= 1.f / direction.GetLength();
		verticalAxis = direction.y;
		horizontalAxis = direction.x;
	}

	void AIInputComponent::SetTargetLocation(Vector2Df newTarget)
	{
		target = newTarget;
	}
}