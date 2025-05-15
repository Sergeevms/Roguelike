#pragma once
#include <Component.h>
namespace Roguelike
{
	class AIChaseTargetComponent :
		public MaxrEngine::Component
	{
	public:
		AIChaseTargetComponent(MaxrEngine::GameObject* gameObject);

		virtual void Update(float deltaTime);
		virtual void Render();

		void SetMaximumChaseRadius(float newMaximumRadius);
		void SetMinimumChaseRadius(float newMinimuRadius);
	private:
		float minumumChaseRadius = 0.f;
		float maximumChaseRadius = 0.f;
	};
}

