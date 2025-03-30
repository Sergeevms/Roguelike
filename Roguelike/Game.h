#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <unordered_map>

namespace Roguelike
{
	enum class GameState;
	class BaseState;

	class Game
	{
	public:
		void StartGame();
		void UpdateGame(const float deltaTime, sf::RenderWindow& window);
		void ToMainMenu();
		void Shutdown();

		Game();

	private:
		void Update(const float deltaTime);
		void HandleInputEvents(sf::RenderWindow& window);
		void Draw(sf::RenderWindow&) const;
		void SwitchToState(GameState newState);
		bool IsGameShuttingDown() const;
		std::vector<std::shared_ptr<BaseState>> stateStack;
	};
}