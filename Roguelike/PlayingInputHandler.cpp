#include "PlayingInputHandler.h"
#include "BaseState.h"
#include "Application.h"

namespace Roguelike
{
	PlayingInputHandler::PlayingInputHandler() : BaseInputHandler()
	{
	}

	void PlayingInputHandler::HandleInputEvents(const std::vector<sf::Event>& input)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			Application::GetInstance().GetGame()->ToMainMenu();
		}
	}
}