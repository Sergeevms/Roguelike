#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>
#include "PerceptionSystem.h"

namespace Roguelike
{
	class OpaqueComponent :
		public MaxrEngine::Component
	{
	public:
		OpaqueComponent(MaxrEngine::GameObject* gameObject);
		~OpaqueComponent();

		virtual void Update(float deltaTime) override;
		virtual void Render() override;
		friend class PerceptionSystem;
	protected:
		sf::FloatRect bounds;
	};
}

