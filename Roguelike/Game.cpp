#include <assert.h>
#include "Game.h"
#include "Application.h"
#include "GameWorld.h"
#include "BaseState.h"
#include "PlayingState.h"
#include "MainMenuState.h"

namespace Roguelike
{
	Game::Game()
	{	
		GameWorld* world = GameWorld::GetWorld();
		stateStack.emplace_back(std::make_shared<MainMenuState>());
	}

	bool Game::IsGameShuttingDown() const
	{
		return stateStack.empty();
	}

	void Game::Update(const float deltaTime)
	{
		stateStack.rbegin()->get()->Update(deltaTime);
	}

	void Game::HandleInputEvents(sf::RenderWindow& window)
	{
		std::vector<sf::Event> inputEvents;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed || event.type == sf::Event::TextEntered)
			{
				inputEvents.push_back(event);
			}
		}
		stateStack.rbegin()->get()->HandleInput(inputEvents);
	}

	void Game::Draw(sf::RenderWindow& window) const
	{
		for (auto& state : stateStack)
		{
			state->Draw(window);
		}
	}

	void Game::SwitchToState(GameState newState)
	{		
		switch (newState)
		{
		case GameState::MainMenu:
		{			
			stateStack.clear();
			stateStack.emplace_back(std::make_shared<MainMenuState>());
			break;
		}
		case GameState::Playing:
		{
			stateStack.clear();
			stateStack.emplace_back(std::make_shared<PlayingState>());
			stateStack.back()->Init();			
			break;
		}
		case GameState::None:
		{
			stateStack.clear();
			break;
		}
		}
	}

	void Game::StartGame()
	{
		SwitchToState(GameState::Playing);
	}

	void Game::UpdateGame(const float deltaTime, sf::RenderWindow& window)
	{
		HandleInputEvents(window);
		if (IsGameShuttingDown())
		{
			window.close();
		}		
		else
		{
			Update(deltaTime);
			window.clear();
			Draw(window);
			window.display();
		}
	}

	void Game::ToMainMenu()
	{
		SwitchToState(GameState::MainMenu);
	}

	void Game::Shutdown()
	{
		SwitchToState(GameState::None);
	}
}