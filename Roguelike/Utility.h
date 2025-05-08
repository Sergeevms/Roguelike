#pragma once
#include "Vector.h"

namespace Roguelike
{	
	template <typename T>
	bool InRect(MaxrEngine::Vector2D<T> rectTopLeft, MaxrEngine::Vector2D<T> rectSize, MaxrEngine::Vector2D<T> position)
	{
		MaxrEngine::Vector2D<T> bottomRight = rectTopLeft + rectSize;
		return (rectTopLeft.x <= position.x && position.x < bottomRight.x)
			&& (rectTopLeft.y <= position.y && position.y < bottomRight.y);
	}
}
