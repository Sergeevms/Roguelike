#include "AIBlackboard.h"

namespace Roguelike
{
	AIBlackboard::AIBlackboard(MaxrEngine::GameObject* gameObject)
		: Component(gameObject)
	{
	}

	void AIBlackboard::Update(float deltaTime)
	{
	}

	void AIBlackboard::Render()
	{
	}

	void AIBlackboard::SetTargetVisible(bool newTargetIsVisible)
	{
		isTargetVisible = newTargetIsVisible;
	}

	void AIBlackboard::SetLastTargetPosition(MaxrEngine::Vector2Df newPosition)
	{
		lastTargetPosition = newPosition;
	}

	bool AIBlackboard::IsTargetVisible() const
	{
		return isTargetVisible;
	}

	const MaxrEngine::Vector2Df& AIBlackboard::GetLastTargetPosition()
	{
		return lastTargetPosition;
	}
}