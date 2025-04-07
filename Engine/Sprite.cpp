#include "pch.h"
#include "Sprite.h"

namespace Engine
{
	void InitSprite(sf::Sprite& sprite, float desiredWidth, float desiredHeight, const sf::Texture& texture)
	{
		sprite.setTexture(texture);
		SetSpriteRelativeOrigin(sprite, 0.5f, 0.5f);
		SetSpriteSize(sprite, desiredWidth, desiredHeight);
	}

	void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight)
	{
		sf::FloatRect spriteRect = sprite.getGlobalBounds();
		sf::Vector2f scale = { desiredWidth / spriteRect.width, desiredHeight / spriteRect.height };
		sprite.setScale(scale);
	}

	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float relativeOriginX, float relativeOriginY)
	{
		sf::FloatRect spriteRect = sprite.getGlobalBounds();
		sprite.setOrigin({ relativeOriginX * spriteRect.width, relativeOriginY * spriteRect.height });
	}

	void DrawSprite(const sf::Sprite& sprite, sf::RenderWindow& window)
	{
		window.draw(sprite);
	}

	sf::Vector2f GetVectorBetweenSprites(const sf::Sprite& spriteFrom, const sf::Sprite& spriteTo)
	{		
		return spriteTo.getPosition() - spriteFrom.getPosition();
	}

	float GetManhattanDistanceBetweenSprites(const sf::Sprite& spriteFrom, const sf::Sprite& spriteTo)
	{
		sf::Vector2f betweenSprites = spriteTo.getPosition() - spriteFrom.getPosition();
		return fabsf(betweenSprites.x) + fabsf(betweenSprites.y);
	}

	bool CheckSpriteIntersection(const sf::Sprite& sprite1, const sf::Sprite& sprite2)
	{
		const auto distance = sprite1.getPosition() - sprite2.getPosition();
		if (sqrtf(distance.x * distance.x + distance.y * distance.y) * 2 < sprite1.getGlobalBounds().width + sprite2.getGlobalBounds().width) {
			return true;
		}
		return false;
	}
}
