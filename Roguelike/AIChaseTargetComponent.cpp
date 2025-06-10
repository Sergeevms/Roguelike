#include "AIChaseTargetComponent.h"
#include "AIBlackboard.h"
#include "GameObject.h"
#include "Utility.h"
#include "AIInputComponent.h"
#include <AtackComponent.h>

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
			MaxrEngine::GameObject* target;
			if (blackBoard->Get("lastTarget", target))
			{
				auto inputComponent = gameObject->GetComponent<MaxrEngine::AIInputComponent>();
				auto betweenVector = target->GetComponent<MaxrEngine::TransformComponent>()->GetWorldPosition() - transform->GetWorldPosition();
				auto distance = betweenVector.GetLength();
				if (InRange(distance, minumumChaseRadius, maximumChaseRadius))
				{
					movingDirection = betweenVector;
					inputComponent->SetDirection(movingDirection);
				}
				auto atackRange = gameObject->GetComponent<MaxrEngine::AtackComponent>()->GetRange();
				if (InRange(distance, 0.f, atackRange))
				{
					inputComponent->SetAtack(true);
				}
			}
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