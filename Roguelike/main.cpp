#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "ResourceSystem.h"
#include "DeveloperLevel.h"
#include "RenderSystem.h"
#include "Matrix2D.h"
#ifdef CREATE_CONSOLE_FOR_ENGINE_PRINT_OUTPUT
#include <iostream>
#include <Windows.h>  
#endif // CREATE_CONSOLE_FOR_ENGINE_PRINT_OUTPUT


int main()
{
#ifdef CREATE_CONSOLE_FOR_ENGINE_PRINT_OUTPUT
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	std::cout << "Test" << std::endl;
#endif // CREATE_CONSOLE_FOR_ENGINE_PRINT_OUTPUT
	
	MaxrEngine::RenderSystem::Instance()->CrateMainWindow(sf::VideoMode(1280, 720), "Roguelike");
	MaxrEngine::ResourceSystem::Instance()->LoadTexture("ball", "Resources/Textures/ball.png");
	MaxrEngine::ResourceSystem::Instance()->LoadMusic("background", "Resources/Sounds/Clinthammer__Background_Music.wav");

	auto developerLevel = std::make_shared<Roguelike::DeveloperLevel>();
	developerLevel->Start();

	MaxrEngine::Engine::Instance()->Run();

	return 0;
}
