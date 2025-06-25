#include "AIAtackComponent.h"
#include "GameObject.h"
#include "AIBlackboard.h"


namespace Roguelike
{
	AIAtackComponent::AIAtackComponent(MaxrEngine::GameObject* gameObject, float cooldown, float damage, float range, std::weak_ptr<MaxrEngine::GameObject> target) 
		: AtackComponent(gameObject, cooldown, damage, range, target)
	{
	}
	void AIAtackComponent::Update(float deltaTime)
	{
		AtackComponent::Update(deltaTime);
		bool targetVisible = false;
		auto blackBoard = gameObject->GetComponent<AIBlackboard>();
		if (currentCooldown <= 0 && blackBoard->Get("isTargetVisible", targetVisible) && targetVisible)
		{
			if (!target.expired())
			{
				auto targetPtr = target.lock();
				auto distance = (gameObject->GetComponent<MaxrEngine::TransformComponent>()->GetWorldPosition() -
					targetPtr->GetComponent<MaxrEngine::TransformComponent>()->GetWorldPosition()).GetLength();
				if (distance <= range)
				{
					Atack();
				}
			}
		}
	}
}