#include "AITargetSelector.h"
#include "AIBlackboard.h"
#include "GameObject.h"
#include "ActorComponent.h"
#include <map>
#include "Settings.h"
#include "PerceptionComponent.h"

namespace Roguelike
{
	AITargetSelector::AITargetSelector(MaxrEngine::GameObject* gameObject)
		: Component(gameObject)
	{
	}

	void AITargetSelector::Update(float deltaTime)
	{		
	}

	void AITargetSelector::Render()
	{
	}

	void AITargetSelector::UpdateTarget()
	{
		std::vector<MaxrEngine::GameObject*>* detectedActors = nullptr;
		gameObject->GetComponent<AIBlackboard>()->Get("Detected Actors", detectedActors);
		std::map<float, MaxrEngine::GameObject*> targets;
		if (detectedActors)
		{
			auto& position = gameObject->GetComponent<MaxrEngine::TransformComponent>()->GetWorldPosition();
			for (auto& actor : *detectedActors)
			{
				if (actor->GetComponent<MaxrEngine::ActorComponent>()->GetGroupID() == ActorsGroups::PlayerGroup)
				{
					auto between = actor->GetComponent<MaxrEngine::TransformComponent>()->GetWorldPosition() - position;
					targets.emplace(std::pair<float, MaxrEngine::GameObject*>(between.GetLength(), actor));
				}
			}
		}
		auto blackBoard = gameObject->GetComponent<AIBlackboard>();
		if (targets.size() > 0)
		{
			blackBoard->Set("isTargetVisible", true);
			blackBoard->Set("lastTargetPosition", targets.begin()->second->GetComponent<MaxrEngine::TransformComponent>()->GetWorldPosition());
			blackBoard->Set("lastTarget", targets.begin()->second);
			Emit();			
		}
		else
		{
			blackBoard->Set("isTargetVisible", false);
		}
	}

	void AITargetSelector::Notify(std::shared_ptr<MaxrEngine::IObservable> observable)
	{
		if (std::dynamic_pointer_cast<MaxrEngine::PerceptionComponent>(observable))
		{
			UpdateTarget();
		}
	}
}