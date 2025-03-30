#include "NotPlayingWindow.h"
#include "BaseInputHandler.h"

namespace Roguelike
{
	void NotPlayingWindow::HandleInput(const std::vector<sf::Event>& input)
	{
		inputHandler->HandleInputEvents(input);
	}
}