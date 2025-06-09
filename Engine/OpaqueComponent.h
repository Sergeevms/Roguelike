#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>
#include "PerceptionSystem.h"

namespace MaxrEngine
{
	class OpaqueComponent :
		public Component
	{
	public:
		ENGINE_API OpaqueComponent(GameObject* gameObject);
		ENGINE_API ~OpaqueComponent();

		ENGINE_API virtual void Update(float deltaTime) override;
		ENGINE_API virtual void Render() override;
		friend class PerceptionSystem;
	protected:
		sf::FloatRect bounds;
	};
}

