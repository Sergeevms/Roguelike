#pragma once
#include <Component.h>
#include "Vector.h"
namespace Roguelike
{
	class AIBlackboard :
		public MaxrEngine::Component
	{
	public:
		AIBlackboard(MaxrEngine::GameObject* gameObject);

		virtual void Update(float deltaTime);
		virtual void Render();

		void SetTargetVisible(bool newTargetIsVisible);
		void SetLastTargetPosition(MaxrEngine::Vector2Df newPosition);
		bool IsTargetVisible() const;
		const MaxrEngine::Vector2Df& GetLastTargetPosition();
	private:
		bool isTargetVisible = false;
		MaxrEngine::Vector2Df lastTargetPosition;
	};
}
