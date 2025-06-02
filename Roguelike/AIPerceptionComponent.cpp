#include "AIPerceptionComponent.h"
#include "AIBlackboard.h"

namespace Roguelike
{
	AIPerceptionComponent::AIPerceptionComponent(MaxrEngine::GameObject* gameObject)
		: PerceptionComponent(gameObject)
	{
		auto blackBoard = gameObject->GetComponent<AIBlackboard>();
		blackBoard->Set("Detected Actors", &detectedActors);
	}
}
