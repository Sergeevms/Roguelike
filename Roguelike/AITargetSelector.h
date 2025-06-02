#pragma once
#include <Component.h>
namespace Roguelike
{
	class AITargetSelector :
		public MaxrEngine::Component
	{
	public:
		AITargetSelector(MaxrEngine::GameObject* gameObject); 
		
		virtual void Update(float deltaTime);
		virtual void Render();
		virtual void UpdateTarget();
	};
}

