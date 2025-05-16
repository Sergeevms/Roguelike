#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include "PhysicsSystem.h"
#include "Collision.h"
#include "Trigger.h"

namespace MaxrEngine
{
	class ColliderComponent :
		public Component
	{
	public:
		ENGINE_API ColliderComponent(GameObject* gameObject);

		virtual void Update(float deltaTime) = 0;
		virtual void Render() = 0;

		ENGINE_API void SetTrigger(bool newIsTrigger);

		ENGINE_API void SubscribeCollision(std::function<void(Collision)> onCollisionAction);
		ENGINE_API void UnsubscribeCollision(std::function<void(Collision)> onCollisionAction);

		ENGINE_API void SubscribeTriggerEntered(std::function<void(Trigger)> onTriggerEntered);
		ENGINE_API void UnsubscribeTriggerEntered(std::function<void(Trigger)> onTriggerEntered);

		ENGINE_API void SubscribeTriggerExit(std::function<void(Trigger)> onTriggerExit);
		ENGINE_API void UnsubscribeTriggerExit(std::function<void(Trigger)> onTriggerExit);

		friend class PhysicsSystem;

	protected:
		sf::FloatRect bounds;
		bool isTrigger = false;

		void OnCollision(Collision collision);
		void OnTriggerEntered(Trigger trigger);
		void OnTriggerExit(Trigger trigger);

		std::vector<std::function<void(Collision)>> onCollisionActions;
		std::vector<std::function<void(Trigger)>> onTriggerEnteredActions;
		std::vector<std::function<void(Trigger)>> onTriggerExitActions;
	};
}

