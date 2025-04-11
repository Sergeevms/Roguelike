#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "ResourceSystem.h"
#include "DeveloperLevel.h"
#include "RenderSystem.h"

int main()
{	
	MaxrEngine::RenderSystem::Instance()->CrateMainWindow(sf::VideoMode(1280, 720), "Roguelike");
	//sf::RenderWindow* window = new sf::RenderWindow(/*sf::VideoMode(1280, 720), "Roguelike"*/);
	//MaxrEngine::RenderSystem::Instance()->SetMainWindow(/*new sf::RenderWindow(sf::VideoMode(1280, 720), "Roguelike")*/window);
	//MaxrEngine::RenderSystem::Instance()->GetMainWindow().create(sf::VideoMode(1280, 720), "Roguelike");
	MaxrEngine::ResourceSystem::Instance()->LoadTexture("ball", "Resources/Textures/ball.png");

	auto developerLevel = std::make_shared<Roguelike::DeveloperLevel>();
	developerLevel->Start();
	MaxrEngine::Engine::Instance()->Run();

	return 0;
}
