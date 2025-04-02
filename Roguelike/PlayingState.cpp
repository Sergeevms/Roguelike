#include "PlayingState.h"
#include "GameWorld.h"
#include "Utility.h"
#include "PlayingInputHandler.h"


namespace Roguelike
{
	PlayingState::PlayingState() : BaseState() 
	{		
		inputHandler = std::make_unique<PlayingInputHandler>();
		textStyle.Init("Roboto-Regular.ttf", sf::Color::Green, sf::Text::Bold);
		toBeDone.setString(L"TO BE DONE…");
		toBeDone.SetStyle(&textStyle);
		toBeDone.setCharacterSize(50);
		SetOriginByRelative(toBeDone, relativePositions.at(RelativePosition::Center));
		pressEsc.setString(L"Press Esc to exit to menu");
		pressEsc.SetStyle(&textStyle);
		pressEsc.setStyle(sf::Text::Italic);
		SetOriginByRelative(pressEsc, relativePositions.at(RelativePosition::Center));
		auto world = GameWorld::GetWorld();
		toBeDone.setPosition(world->ScreenCenter() - sf::Vector2f(0.f, toBeDone.GetRect().height));
		pressEsc.setPosition(world->ScreenCenter() + sf::Vector2f(0.f, pressEsc.GetRect().height));
	}

	void PlayingState::Draw(sf::RenderWindow& window) const
	{
		toBeDone.Draw(window);
		pressEsc.Draw(window);
	}

	void PlayingState::Update(const float deltaTime)
	{
	}

	void PlayingState::Init()
	{
	}
}