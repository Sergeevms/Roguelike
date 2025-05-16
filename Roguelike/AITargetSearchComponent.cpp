#include "AITargetSearchComponent.h"
#include "AIBlackboard.h"
#include "TransformComponent.h"

namespace Roguelike
{
	AITargetSearchComponent::AITargetSearchComponent(MaxrEngine::GameObject* gameObject) :
		Component(gameObject)
	{
	}

	void AITargetSearchComponent::Update(float deltaTime)
	{
		if (target)
		{
			auto targetTransform = target->GetComponent<MaxrEngine::TransformComponent>();
			auto selfTransform = gameObject->GetComponent<MaxrEngine::TransformComponent>();
			auto betweenVector = targetTransform->GetWorldPosition() - selfTransform->GetWorldPosition();
			auto blackBoard = GetGameObject()->GetComponent<AIBlackboard>();
			if (betweenVector.GetLength() <= detectionRange)
			{				
				blackBoard->Set("isTargetVisible", true);
				blackBoard->Set("lastTargetPosition", targetTransform->GetWorldPosition());
			}
			else
			{
				blackBoard->Set("isTargetVisible", true);
			}
		}
	}

	void AITargetSearchComponent::Render()
	{
	}

	void AITargetSearchComponent::SetSearchTarget(MaxrEngine::GameObject* newTarget)
	{
		target = newTarget;
	}

	void Roguelike::AITargetSearchComponent::SetDetectionRange(float newDetectionRange)
	{
		detectionRange = newDetectionRange;
	}
}