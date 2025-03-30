#pragma once
#include "BaseState.h"
#include "PauseMenu.h"

namespace  Roguelike
{
	class PauseState : public BaseState
	{
	public:
		PauseState();
		virtual ~PauseState() = default;
		virtual void Draw(sf::RenderWindow& window) const  override;
	private:
		sf::RectangleShape overallBackground;
		sf::RectangleShape menuBackground;
		PauseMenu menu;
	};
}

