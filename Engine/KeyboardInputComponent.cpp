#include "pch.h"
#include "KeyboardInputComponent.h"
#include <SFML/Graphics.hpp>

namespace MaxrEngine
{
	KeyboardInputComponent::KeyboardInputComponent(GameObject* gameObject) :
		InputComponent(gameObject)
	{
	}

	void KeyboardInputComponent::Update(float deltaTime)
	{
		verticalAxis = 0.f;
		horizontalAxis = 0.f;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			verticalAxis += 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			verticalAxis -= 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			horizontalAxis += 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			horizontalAxis -= 1.0f;
		}
	}
}