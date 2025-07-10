#pragma once
#include "AttackComponent.h"
namespace Roguelike
{
	class AIAtackComponent :
		public AtackComponent
	{
	public:
		AIAtackComponent(MaxrEngine::GameObject* gameObject, float cooldown = 0.f, float damage = 0.f, float range = 0.f,
			std::weak_ptr<MaxrEngine::GameObject> target = std::weak_ptr<MaxrEngine::GameObject>());
		virtual void Update(float deltaTime);
	};
}

