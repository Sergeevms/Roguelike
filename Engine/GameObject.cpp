#include "pch.h"
#include "GameObject.h"
#include <assert.h>
#include "Sprite.h"
namespace Engine
{
	GameObject::GameObject(const std::string& texturePath, const sf::Vector2f& position, float width, float height)
		: startPosition(position)
	{
		assert(texture.loadFromFile(texturePath));
		InitSprite(sprite, width, height, texture);
		sprite.setPosition(position);
	}

	void GameObject::Draw(sf::RenderWindow& window)
	{
		window.draw(sprite);
	}

	void GameObject::Restart()
	{
		sprite.setPosition(startPosition);
	}
}