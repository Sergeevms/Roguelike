#pragma once
#include <map>
#include <vector>
#include "EngineAPI.h"

namespace MaxrEngine
{
	class ColliderComponent;
	class PhysicsSystem
	{
	public:
		ENGINE_API static PhysicsSystem* Instance();

		void Update();

		ENGINE_API float GetFixedDeltaTime() const;
		ENGINE_API void Subscribe(ColliderComponent* collider);
		ENGINE_API void Unsubscribe(ColliderComponent* collider);
	private:
		PhysicsSystem() {};
		~PhysicsSystem() {};

		PhysicsSystem(PhysicsSystem const&) = delete;
		PhysicsSystem& operator=(PhysicsSystem const&) = delete;
		
		std::vector<ColliderComponent*> colliders;
		std::map<ColliderComponent*, ColliderComponent*> triggersEnteredPair;

		float fixedDeltaTime = 0.02f;
	};
}

