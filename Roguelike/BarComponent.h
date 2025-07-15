#pragma once
#include <Component.h>
#include "Vector.h"
#include "SFML/Graphics.hpp"

namespace Roguelike
{
	class BarComponent :
		public MaxrEngine::Component
	{
	public:
		BarComponent(MaxrEngine::GameObject* gameObject, MaxrEngine::Vector2Df centerOffset = { 0.f, 0.f }, 
			MaxrEngine::Vector2Df barSize = { 1.f,0.f }, sf::Color barColor = sf::Color::White, float borderSize = 0.f, float maxAmount = 1.f);

		virtual void Update(float deltaTime) = 0;
		virtual void Render() override;

		MaxrEngine::Vector2Df GetCenterOffset() const;
		void SetCenterOffset(const MaxrEngine::Vector2Df& newCenterOffset);

		MaxrEngine::Vector2Df GetBarSize() const;
		void SetBarSize(const MaxrEngine::Vector2Df& newBarSize);

		sf::Color GetBarColor() const;
		void SetBarColor(const sf::Color newBarColor);

		float GetMaxAmount() const;
		void SetMaxAmount(const float newMaxAmount);

		float GetCurrentAmount() const;
		void SetCurrentAmount(const float newCurrentAmount);

		float GetBorderSize() const;
		void SetBorderSize(const float newBorderSize);
	protected:
		MaxrEngine::Vector2Df centerOffset;
		MaxrEngine::Vector2Df barSize;
		sf::Color barColor;
		float maxAmount;
		float currentAmount;
		float borderSize;
	};
}

