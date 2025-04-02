#include "BaseState.h"
#include "BaseInputHandler.h"

namespace Roguelike
{
	void BaseState::HandleInput(const std::vector<sf::Event>& input)
	{
		inputHandler->HandleInputEvents(input);
	}
}