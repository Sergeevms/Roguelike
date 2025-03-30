#pragma once
#include "IGameObject.h"
namespace Roguelike
{
	enum class Direction;

	class IPlatformObject : public virtual IGameObject
	{
	public:
		virtual void SetMovingDirection(const Direction direction) = 0;
	};
}

