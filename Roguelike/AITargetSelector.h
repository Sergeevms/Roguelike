#pragma once
#include "Component.h"
#include "IObserver.h"
namespace Roguelike
{
	class AITargetSelector :
		public MaxrEngine::Component, virtual public MaxrEngine::IObservable, virtual public MaxrEngine::IObserver
	{
	public:
		AITargetSelector(MaxrEngine::GameObject* gameObject); 
		
		virtual void Update(float deltaTime) override;
		virtual void Render() override;
		virtual void UpdateTarget();
		virtual void Notify(std::shared_ptr<MaxrEngine::IObservable> observable) override;
	};
}

