#pragma once
#include <SFML/Graphics.hpp>
namespace MaxrEngine
{
	class ColliderComponent;
	struct Collision
	{
	public:
		Collision(ColliderComponent* first, ColliderComponent* second, sf::FloatRect collisionRect) :
			first(first), second(second), collisionRect(collisionRect) {
		};
	private:
		ColliderComponent* first;
		ColliderComponent* second;
		sf::FloatRect collisionRect;
	};
}