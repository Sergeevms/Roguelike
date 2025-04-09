#pragma once
#include "Component.h"
#include "TransformComponent.h"
#include <SFML/Graphics.hpp>
namespace MaxrEngine
{
	class SpriteRendererComponent :
		public Component
	{
	public:
		SpriteRendererComponent(GameObject* gameObject);
		~SpriteRendererComponent();

		virtual void Update(float deltaTime) override;
		virtual void Render() override;

		const sf::Sprite* GetSprite() const;
		void SetTexture(const sf::Texture& newTexture);
		void SetPixelSize(int newWidth, int newHeight);

		void FlipX(bool flip);
		void FlipY(bool flip);
	private:
		sf::Sprite* sprite;
		TransformComponent* transform;

		bool isFlipX = false;
		bool isFlipY = false;
	};
}

