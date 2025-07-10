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
		if (blackBoard)
		{
			bool isTargetVisible = false;
			MaxrEngine::Vector2Df movingDirection;
			auto inputComponent = gameObject->GetComponent<MaxrEngine::AIInputComponent>();
			if (blackBoard->Get("isTargetVisible", isTargetVisible) && isTargetVisible)
			{
				auto transform = gameObject->GetComponent<MaxrEngine::TransformComponent>();
				MaxrEngine::GameObject* target = nullptr;
				if (blackBoard->Get("lastTarget", target))
				{
					auto betweenVector = target->GetComponent<MaxrEngine::TransformComponent>()->GetWorldPosition() - transform->GetWorldPosition();
					auto distance = betweenVector.GetLength();
					if (InRange(distance, minumumChaseRadius, maximumChaseRadius))
					{
						movingDirection = betweenVector;
					}
				}
			}
			inputComponent->SetDirection(movingDirection);
		}
		else
		{
			LOG_ERROR("AIBlackboard requried for AIChaseComponent");
		}
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