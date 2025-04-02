#pragma once
#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>

namespace Roguelike
{
	enum class ActionsTypesOnInput;

	class GameWorld
	{
	public:
		static GameWorld* GetWorld()
		{
			static GameWorld world;
			return &world;
		};
		sf::Vector2f ScreenCenter();
		sf::Vector2f ScreenSize();

		//General settings

		int screenWidth;
		int screenHeight;
		std::wstring gameName;
		float timePerFrame;

		//Sound settings

		bool musicOn;
		bool soundOn;		
				
		//Paths to files

		std::string resourcesPath;
		std::string soundPath;
		std::string fontPath;
		std::string texturePath;
		std::string recordsFileName;
		
		//Control settings
		std::unordered_map<sf::Keyboard::Key, ActionsTypesOnInput> keyMap;
	private:
		GameWorld();
		~GameWorld() = default;
		GameWorld(const GameWorld&) = delete;
		GameWorld operator= (const GameWorld&) = delete;
	};
};