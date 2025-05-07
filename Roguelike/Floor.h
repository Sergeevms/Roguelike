#pragma once
#include "GameObject.h"

namespace Roguelike
{
	class Floor
	{
	public:
		Floor(MaxrEngine::Vector2Df position, int textureIndex, MaxrEngine::Vector2Di size);
		MaxrEngine::GameObject* GetGameObject();
	private:
		MaxrEngine::GameObject* gameObject;
	};
}

