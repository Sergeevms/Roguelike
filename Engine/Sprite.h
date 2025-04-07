#pragma once
#include <SFML/Graphics.hpp>
#include <list>

namespace Engine
{
	void InitSprite(sf::Sprite& sprite, float desiredWidth, float desiredHeight, const sf::Texture& texture);
	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);
	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float relativeOriginX, float relativeOriginY);

	void DrawSprite(const sf::Sprite& sprite, sf::RenderWindow& window);
	template<class InputIt>
	void DrawSprites(InputIt first, const InputIt last, sf::RenderWindow& window)
	{
		for (; first != last; ++first)
		{
			DrawSprite(*first, window);
		}
	}
	
	sf::Vector2f GetVectorBetweenSprites(const sf::Sprite& spriteFrom, const sf::Sprite& spriteTo);
	float GetManhattanDistanceBetweenSprites(const sf::Sprite& spriteFrom, const sf::Sprite& spriteTo);

	//Checks if sprite1 has intersection with sprite
	bool CheckSpriteIntersection(const sf::Sprite& sprite1, const sf::Sprite& sprite2);
	//Checks if sprite has intersection with at least one sprite in iterated sprites
	template<class InputIt>
	bool CheckSpriteIntersection(InputIt first, const InputIt last, const sf::Sprite& sprite)
	{
		for (; first != last; ++first)
		{
			if (CheckSpriteIntersection(*first, sprite))
				return true;
		}
		return false;
	}
}