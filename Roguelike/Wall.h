#pragma once
#include "Vector.h"
#include "GameObject.h"

namespace Roguelike
{
	enum class WallType
	{
		left,
		top,
		right,
		bottom,
		leftTopCorner,
		rightTopCorner,
		rigthBottomCorner,
		leftBottomCorner
	};

	class Wall
	{
	public:
		Wall(const MaxrEngine::Vector2Df position, int textureIndex, const MaxrEngine::Vector2Di size);
	private:
		MaxrEngine::GameObject* gameObject;
	};
}

