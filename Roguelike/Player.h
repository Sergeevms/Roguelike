#pragma once

#include "GameObject.h"

namespace Roguelike
{
	class Player
	{
	public:
		Player();
		MaxrEngine::GameObject* GetGameObject();
	private:
		MaxrEngine::GameObject* gameObject;
	};
}

