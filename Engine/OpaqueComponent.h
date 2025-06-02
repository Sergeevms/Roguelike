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
		OpaqueComponent(GameObject* gameObject);
		friend class PerceptionSystem;
	protected:
		sf::FloatRect bounds;
	};
}

