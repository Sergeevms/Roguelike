#pragma once
#include "PerceptionComponent.h"
#include "IObserver.h"
namespace Roguelike
{
	class AIPerceptionComponent :
		public MaxrEngine::PerceptionComponent, public MaxrEngine::IObserver
	{
	public:
		AIPerceptionComponent(MaxrEngine::GameObject* gameObject);
		virtual void Notify(std::shared_ptr<IObservable> observable) override;
	};
}

