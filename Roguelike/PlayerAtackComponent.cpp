#include "PlayerAtackComponent.h"
#include "ActorRegisterSystem.h"
#include "InputComponent.h"
#include "Settings.h"
#include "Logger.h"
#include <map>
#include "GameObject.h"

namespace Roguelike
{
	PlayerAtackComponent::PlayerAtackComponent(MaxrEngine::GameObject* gameObject, float cooldown, float damage, float range, std::weak_ptr<MaxrEngine::GameObject> target)
		: AtackComponent(gameObject, cooldown, damage, range, target)
	{
	}

	void PlayerAtackComponent::Notify(std::shared_ptr<MaxrEngine::IObservable> observable)
	{
		if (auto input = std::dynamic_pointer_cast<MaxrEngine::InputComponent>(observable))
		{
			if (currentCooldown <= 0.f)
			{
				currentCooldown = cooldown;
				auto position = gameObject->GetComponent<MaxrEngine::TransformComponent>()->GetWorldPosition();
				auto targetsVector = ActorRegisterSystem::Instance()->GetActorsNotInGroupList(ActorsGroups::PlayerGroup);
				std::map<float, MaxrEngine::GameObject*> targets;
				for (auto& possibleTarget : targetsVector)
				{
					targets.emplace(std::pair<float, MaxrEngine::GameObject*>((possibleTarget->GetComponent<MaxrEngine::TransformComponent>()->GetWorldPosition() 
						- position).GetLength(), possibleTarget));
				}
				auto newTarget = targets.begin();
				if (newTarget->first > range)
				{
					LOG_INFO("Closest target out of range");
				}
				else
				{
					target = newTarget->second->weak_from_this();
					Atack();
				}
			}
			else
			{
				LOG_INFO("Atack is on cooldown");
			}
		}
	}
}
