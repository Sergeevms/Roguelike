#pragma once
#include "GameObjectContainer.h"

namespace Roguelike
{
	class Enemy :
		public GameObjectContainer
	{
	public:
		Enemy();
		MaxrEngine::Vector2Df target;
	};

}
