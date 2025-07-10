#include "AIPerceptionComponent.h"
#include "AIBlackboard.h"
#include "AIInputComponent.h"

namespace Roguelike
{
	AIPerceptionComponent::AIPerceptionComponent(MaxrEngine::GameObject* gameObject)
		: PerceptionComponent(gameObject)
	{
		auto blackBoard = gameObject->GetComponent<AIBlackboard>();
		if (blackBoard)
		{
			blackBoard->Set("Detected Actors", &detectedActors);
		}
		else
		{
			LOG_WARN("AIBlackboard required for  AIPerceptionComponent");
		}
	}

	void AIPerceptionComponent::Notify(std::shared_ptr<IObservable> observable)
	{
		if (auto input = std::dynamic_pointer_cast<MaxrEngine::AIInputComponent>(observable))
		{
			SetVisionDirection(input->GetDirection());
		}
	}
}
