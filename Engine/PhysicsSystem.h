#pragma once
#include <map>
#include <vector>

namespace MaxrEngine
{
	class ColliderComponent;
	class PhysicsSystem
	{
	public:
		static PhysicsSystem* Instance();

		void Update();

		float GetFixedDeltaTime() const;
		void Subscribe(ColliderComponent* collider);
		void Unsubscribe(ColliderComponent* collider);
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

