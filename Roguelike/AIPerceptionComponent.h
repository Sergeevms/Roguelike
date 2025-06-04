#pragma once
#include "PerceptionComponent.h"
#include "IObserver.h"
namespace Roguelike
{
	class AIPerceptionComponent :
		public MaxrEngine::PerceptionComponent
	{
	public:
		AIPerceptionComponent(MaxrEngine::GameObject* gameObject);
	};
}

