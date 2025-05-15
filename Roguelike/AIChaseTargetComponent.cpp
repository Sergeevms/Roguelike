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
		auto controller = gameObject->GetComponent<AIBlackboard>();
		auto transform = gameObject->GetComponent<MaxrEngine::TransformComponent>();
		auto betweenVector = controller->GetLastTargetPosition() - transform->GetWorldPosition();
		auto input = gameObject->GetComponent<MaxrEngine::AIInputComponent>();
		if (controller->IsTargetVisible() && InRange(betweenVector.GetLength(), minumumChaseRadius, maximumChaseRadius))
		{		
			input->SetDirection(betweenVector);
		}
		else
		{			
			input->SetDirection({ 0.f, 0.f });			
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