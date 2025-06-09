#include "AIChaseTargetComponent.h"
#include "AIBlackboard.h"
#include "GameObject.h"
#include "Utility.h"
#include "AIInputComponent.h"

namespace Roguelike
{
	AIChaseTargetComponent::AIChaseTargetComponent(MaxrEngine::GameObject* gameObject)
		: Component(gameObject)
	{
	}

	void AIChaseTargetComponent::Update(float deltaTime)
	{
		auto blackBoard = gameObject->GetComponent<AIBlackboard>();
		bool isTargetVisible = false;
		MaxrEngine::Vector2Df movingDirection;
		if (blackBoard->Get("isTargetVisible", isTargetVisible) && isTargetVisible)
		{
			auto transform = gameObject->GetComponent<MaxrEngine::TransformComponent>();
			MaxrEngine::Vector2Df lastTargetPosition;
			if (blackBoard->Get("lastTargetPosition", lastTargetPosition))
			{
				auto betweenVector = lastTargetPosition - transform->GetWorldPosition();
				if (InRange(betweenVector.GetLength(), minumumChaseRadius, maximumChaseRadius))
				{
					movingDirection = betweenVector;
				}
			}
		}
		auto inputComponent = gameObject->GetComponent<MaxrEngine::AIInputComponent>();
		inputComponent->SetDirection(movingDirection);
	}

	void AIChaseTargetComponent::Render()
	{
	}

	void AIChaseTargetComponent::SetMaximumChaseRadius(float newMaximumRadius)
	{
		maximumChaseRadius = newMaximumRadius;
	}

	void AIChaseTargetComponent::SetMinimumChaseRadius(float newMinimuRadius)
	{
		minumumChaseRadius = newMinimuRadius;
	}
}