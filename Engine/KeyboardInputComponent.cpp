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
		atack = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			LOG_INFO("Forward input");
			verticalAxis += 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			LOG_INFO("Backward input");
			verticalAxis -= 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			LOG_INFO("Up input");
			horizontalAxis += 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			LOG_INFO("Up input");
			horizontalAxis -= 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			LOG_INFO("Atack input");
			atack = true;
			Emit();
		}
	}
}