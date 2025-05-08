#pragma once
#include "Vector.h"
#include "GameObject.h"

namespace Roguelike
{
	class Wall
	{
	public:
		Wall(const MaxrEngine::Vector2Df position, int textureIndex, const MaxrEngine::Vector2Di size);
		MaxrEngine::GameObject* GetGameObject();
	private:
		MaxrEngine::GameObject* gameObject;
	};
}

