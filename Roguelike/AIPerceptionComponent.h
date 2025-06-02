#pragma once
#include <PerceptionComponent.h>
namespace Roguelike
{
	class AIPerceptionComponent :
		public MaxrEngine::PerceptionComponent
	{
	public:
		AIPerceptionComponent(MaxrEngine::GameObject* gameObject);
	};
}

