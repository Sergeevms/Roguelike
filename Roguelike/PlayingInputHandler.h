#pragma once
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "BaseInputHandler.h"

namespace Roguelike
{
	class PlayingInputHandler : public BaseInputHandler
	{
	public:
		PlayingInputHandler();
		virtual void HandleInputEvents(const std::vector<sf::Event>& input) override;
	};
}